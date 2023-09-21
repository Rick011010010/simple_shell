#include "header.h"

/**
 * main - init data
 * @argc: array
 * @argv: array
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	data t;
	(void)argc;
	init(&t, argv[0]);
	exec(&t);

	return (0);
}
