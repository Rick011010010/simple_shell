#include "shell.h"

/**
 * interactive1 - if shell is in interactive mode, returns true.
 * @info: struct address.
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive1(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim1 - checks if char is a delimiter.
 * @b: the character to check.
 * @delim: the delimiter string.
 * Return: 1 if true, 0 if false.
 */
int is_delim1(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * _isalpha1 - checks if the character is alphabetic.
 * @b: The char to input.
 * Return: 1 if b is alphabetic, 0 otherwise.
 */
int _isalpha1(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi1 - converts a string into an integer.
 * @str: the string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise.
 */
int _atoi1(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
