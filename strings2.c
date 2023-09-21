#include "header.h"

/**
 * _strdup - duplicate strings
 * @s: string
 * Return: a pointer
 */
char *_strdup(const char *s)
{
	int j, l = 0;
	char *rslt;

	if (s == NULL)
		return (NULL);

	while (s[l] != '\0')
		l++;

	rslt = (char *)malloc((l + 1) * sizeof(char));

	if (rslt == NULL)
		return (NULL);

	for (j = 0; j <= l; j++)
		rslt[j] = s[j];

	return (rslt);
}


/**
 * _isnumber - checks if a string is a number
 * @stat: status
 * Return: void
 */
int _isnumber(const char *stat)
{
	if (stat == NULL || stat[0] == '\0')
		return (0);
	while (*stat)
	{
		if (!_isdigit(*stat))
			return (0);
		stat++;
	}
	return (1);
}


/**
 * _isdigit - checks if charachter is number
 * @i: charachter
 * Return: 1 if its a digit 0 otherwise
 */
int _isdigit(int i)
{
	return (i >= '0' && i <= '9');
}

