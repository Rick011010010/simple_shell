#include "shell.h"

/**
 * Eputs - Print an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void Eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * Eputchar - Write the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int Eputchar(char c)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buffer, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buffer[i++] = c;
    return (1);
}

/**
 * Putfd - Write the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int Putfd(char c, int fd)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buffer[i++] = c;
    return (1);
}

/**
 * Putsfd - Print an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int Putsfd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return (0);
    while (*str)
    {
        count += Putfd(*str++, fd);
    }
    return (count);
}
