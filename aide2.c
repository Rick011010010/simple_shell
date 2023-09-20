#include "header.h"

/**
 * _perror - print error
 * @s1: first string
 * @s2: second string
 */
void _perror(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return;

	while (*s1)
	{
		write(STDERR_FILENO, s1, 1);
		s1++;
	}

	write(STDERR_FILENO, ": ", 2);

	while (*s2)
	{
		write(STDERR_FILENO, s2, 1);
		s2++;
	}
	write(STDERR_FILENO, "\n", 1);
}


/**
 * _trim - removes spaces and tabs from a string
 * @s: string
 */

void _trim(char *s)
{
	int n, m, l = _strlen(s);

	for (n = 0; n < l && (s[n] == ' ' || s[n] == '\t'); n++)
		;

	for (m = 0; n < l ; n++, m++)
		s[m] = s[n];

	s[m] = '\0';

	for (n = _strlen(s) - 1; n > 0 && (s[n] == ' ' || s[n] == '\t'); n--)
		s[n] = '\0';
}


/**
 * _realloc - reallocates a memory
 * @p: pointer
 * @new_size: new size
 *
 * Return: the newly allocated memory
 */
void *_realloc(void *p, unsigned int new_size)
{
	char *q;
	unsigned int n, np = new_size, old_size = sizeof(p);

	if (old_size == new_size)
		return (p);
	if (p == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
		np = old_size;

	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}

	q = malloc(new_size);

	for (n = 0; n < np; n++)
		q[n] = ((char *)p)[n];
	free(p);
	return (q);
}
