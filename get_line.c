#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buffer: Address of buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t inputBuf(info_t *info, char **buffer, size_t *len)
{
    ssize_t read_result = 0;
    size_t len_p = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        read_result = getline(buffer, &len_p, stdin);
#else
        read_result = _getline(info, buffer, &len_p);
#endif
        if (read_result > 0)
        {
            if ((*buffer)[read_result - 1] == '\n')
            {
                (*buffer)[read_result - 1] = '\0'; /* remove trailing newline */
                read_result--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);
            *len = read_result;
            info->cmd_buf = buffer;
        }
    }
    return (read_result);
}

/**
 * getInput - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t getInput(info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t read_result = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    read_result = input_buf(info, &buf, &len);
    if (read_result == -1) /* EOF */
        return (-1);
    if (len) /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* pass back pointer to current command position */
        return (_strlen(p)); /* return length of current command */
    }

    *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
    return (read_result); /* return length of buffer from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buffer: Buffer.
 * @i: Size.
 *
 * Return: Read result.
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *i)
{
    ssize_t read_result = 0;

    if (*i)
        return (0);
    read_result = read(info->readfd, buffer, READ_BUF_SIZE);
    if (read_result >= 0)
        *i = read_result;
    return (read_result);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Read result.
 */
int Getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t read_result = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    read_result = read_buf(info, buf, &len);
    if (read_result == -1 || (read_result == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * _sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

