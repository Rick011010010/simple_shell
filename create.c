#include "header.h"

/**
 * exec_create - check if built in and then exec
 * @t: data
 * Return: 1 if built in, 0 if not
 */
int exec_create(data *t)
{
	create create[] = {
		{"exit", create_exit},
		{"env", create_env},
		{"setenv", create_setenv},
		{"unsetenv", create_unsetenv},
		{"cd", create_cd},
		{NULL, NULL},
	};
	int n = 0;

	for (n = 0; create[n].cmd; n++)
	{
		if (_strcmp(t->argv[0], create[n].cmd) == 0)
		{
			create[n].f(t);
			return (1);
		}
	}
	return (0);
}

/**
 * create_exit - exits the shell
 * @t: data
 */
void create_exit(data *t)
{
	const char *errorString = "./hsh: 1: exit: Illegal number: ";

	if (t->argv[1])
	{
		if (t->argv[1][0] != '-' && _isnumber(t->argv[1]))
			t->last_exit_stat = atoi(t->argv[1]);
		else
		{
			write(STDERR_FILENO, errorString, strlen(errorString));
			write(STDERR_FILENO, t->argv[1], strlen(t->argv[1]));
			write(STDERR_FILENO, "\n", 1);
			t->last_exit_stat = 2;
		}
	}
	free_array(t->argv);
	free(t->cmd);
	if (t->flag)
		free_array(environ);
	exit(t->last_exit_stat);
}

/**
 * create_env - prints environment
 * @t: data
 */
void create_env(data *t)
{
	int n = 0;

	(void)t;
	while (environ[n])
	{
		_printf(environ[n]);
		_printf("\n");
		n++;
	}
}
/**
 * create_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @t: data
 */

void create_setenv(data *t)
{
	(void)t;
	if (t->argv[1] && t->argv[2])
	{
		if (_setenv(t, t->argv[1], t->argv[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * create_unsetenv - Removes an environment variable
 * @t: data
 */
void create_unsetenv(data *t)
{
	int n, m;
	int l;

	(void)t;
	if (!t->argv[1] || !getenv(t->argv[1]))
	{
		_perror(t->shell, "variable not found.");
		return;
	}
	l = strlen(t->argv[1]);
	for (n = 0; environ[n]; n++)
		if (strncmp(environ[n], t->argv[1], l) == 0 && environ[n][l] == '=')
			for (m = n; environ[m]; m++)
				environ[m] = environ[m + 1];
}
