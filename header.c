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

/**
 * create_cd - handle the command cd
 * @t: data
 */
void create_cd(data *t)
{
	char *d = t->argv[1];
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	_setenv(t, "PWD", cwd);
	if (!d)
		d = _getenv("HOME");
	if (chdir(d) == -1)
		perror("cd");
	else
	{
		_setenv(t, "OLDPWD", _getenv("PWD"));
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		_setenv(t, "PWD", cwd);
	}
}
