#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *file_path)
{
    struct stat st;

    (void)info;
    if (!file_path || stat(file_path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (path_str[i] != ':')
            buf[k++] = path_str[i];
    buf[k] = 0;
    return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *path_str, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_str)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            path = dup_chars(path_str, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);
            if (!path_str[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}

