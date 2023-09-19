#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @source: The source string.
 * @n: The number of characters to be copied.
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, char *source, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    while (source[i] != '\0' && i < n - 1)
    {
        dest[i] = source[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return (result);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @source: The second string.
 * @n: The maximum number of bytes to be used.
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *source, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (source[j] != '\0' && j < n)
    {
        dest[i] = source[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0';
    return (result);
}

/**
 * _strchr - Locates a character in a string.
 * @str: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area `str`.
 */
char *_strchr(char *str, char c)
{
    do
    {
        if (*str == c)
            return (str);
    } while (*str++ != '\0');

    return (NULL);
}

