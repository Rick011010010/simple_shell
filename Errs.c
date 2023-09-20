#include "shell.h"

/**
 * _erratoi3 - Convert a string to an integer.
 * @str: The string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise,
 *         -1 on error.
 */
int _erratoi3(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++; /* TODO: why does this make main return 255? */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error3 - Print an error message.
 * @info: The parameter and return info structure.
 * @error_str: String containing the specified error type.
 */
void print_error3(info_t *info, char *error_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_str);
}

/**
 * print_d3 - Print a decimal (integer) number (base 10).
 * @number: The input number.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_d3(int number, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (number < 0)
	{
		abs_value = -number;
		__putchar('-');
		count++;
	}
	else
		abs_value = number;
	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number3 - Converter function, a clone of itoa.
 * @num: The number.
 * @base: The base.
 * @flags: Argument flags.
 * Return: The string representation of the number.
 */
char *convert_number3(long int num, int base, int flags)
{
	static char *char_set;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	char_set = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = char_set[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments3 - Replace the first instance of '#' with '\0'.
 * @str: The address of the string to modify.
 */
void remove_comments3(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '#' && (!i || str[i - 1] == ' '))
		{
			str[i] = '\0';
			break;
		}
	}
}

