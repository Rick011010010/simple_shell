#include "header.h"

/**
 * _printf - print a string to stander out put
 * @s: string
 */
void _printf(const char *s)
{
	if (!s)
		return;
	while (*s)
	{
		write(STDOUT_FILENO, s, 1);
		s++;
	}
}

/**
 * free_array - free an array
 * @ar: array
 */
void free_array(char **ar)
{
	int n;

	if (!ar)
		return;

	for (n = 0; ar[n]; n++)
	{
		free(ar[n]);
		ar[n] = NULL;
	}

	free(ar);
}

/**
 * split - split string
 * @t: data
 * @delim: string input
 */
void split(data *t, const char *delim)
{
	char *toke;
	int ntoke = 0;

	t->argv = malloc(2 * sizeof(char *));
	if (t->argv == NULL)
	{
		free(t->cmd);
		perror(t->shell);
		exit(EXIT_FAILURE);
	}
	t->argv[0] = NULL;
	t->argv[1] = NULL;

	toke = strtok(t->cmd, delim);
	while (toke)
	{
		t->argv = realloc(t->argv, (ntoke + 2) * sizeof(char *));
		if (t->argv == NULL)
			goto free;
		t->argv[ntoke] = _strdup(toke);
		if (t->argv[ntoke] == NULL)
			goto free;
		ntoke++;
		toke = strtok(NULL, delim);
	}
	t->argv[ntoke] = NULL;
	return;
free:
	free_array(t->argv);
	free(t->cmd);
	perror(t->shell);
	exit(EXIT_FAILURE);
}

/**
 * init - init data
 * @t: data
 * @shell: input
 */

void init(data *t, const char *shell)
{
	t->cmd = NULL;
	t->argv = NULL;
	t->shell = shell;
	t->last_exit_stat = EXIT_SUCCESS;
	t->flag = 0;
}

/**
 * read_cmd - read the command
 * @t: data
 */
void read_cmd(data *t)
{
	size_t k = 0;
	ssize_t nread;
	int n = 0;

	nread = getline(&t->cmd, &k, stdin);

	if (nread == -1)
	{
		free(t->cmd);
		exit(EXIT_SUCCESS);
	}

	t->cmd[nread - 1] = '\0';
	_trim(t->cmd);
	for (n = 0; t->cmd[n] != '\0'; n++)
	{
		if (t->cmd[0] == '#' || (t->cmd[n] == '#' && t->cmd[n - 1] == ' '))
		{
			t->cmd[n] = '\0';
			break;
		}
	}
	_trim(t->cmd);
}
