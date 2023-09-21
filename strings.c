#include "header.h"

/**
 * _strlen - string length
 * @s: string
 * Return: number of char in s.
 */
unsigned int _strlen(char *s)
{
	unsigned int j;

	for (j = 0; s[j] != '\0'; j++)
		;
	return (j);
}


/**
 * _strcmp - compares strings.
 * @s1: string 1
 * @s2: string 2
 *
 * Return: returns an integer indicating the result of the comparison
 */
int _strcmp(const char *s1, const char *s2)
{
	int j;
	int rest = 0;

	for (j = 0; s1[j] != '\0' && s2[j] != '\0'; j++)
	{
		if (s1[j] != s2[j])
		{
			rest = s1[j] - s2[j];
			break;
		}
	}

	return (rest);
}

/**
 * _strncmp - compares strings.
 * @s1: string
 * @s2: string
 * @n: input
 * Return: returns an integer indicating the result of the comparison
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int j;
	int rest = 0;

	for (j = 0; s1[j] != '\0' && s2[j] != '\0'; j++)
	{

		if (j >= n)
			break;
		if (s1[j] != s2[j])
		{
			rest = s1[j] - s2[j];
			break;
		}
	}

	return (rest);
}

/**
 * _strcpy - copy strings.
 * @d: destination
 * @src: source
 * Return: char *
 */
char *_strcpy(char *d, const char *src)
{
	int l;

	for (l = 0; src[l] != '\0'; ++l)
	{
		d[l] = src[l];
	}
	d[l] = '\0';
	return (d);
}

/**
 * _strcat - concatenate strings
 * @d: destination
 * @src: source
 * Return: Nothing
 */
char *_strcat(char *d, const char *src)
{
	char *rslt = d;

	while (*d != '\0')
		d++;

	while (*src != '\0')
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';

	return (rslt);
}
