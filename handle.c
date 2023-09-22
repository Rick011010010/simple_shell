#include "header.h"

/**
 * start - start process
 * @t: data
 */

void start(data *t)
{
	pid_t child_pid = fork();
	int stat = 0;

	if (child_pid == -1)
		goto free;
	if (child_pid == 0 && execve(t->argv[0], t->argv, NULL) == -1)
		goto free;
	else if (wait(&stat) == -1)
		goto free;
	if (WIFEXITED(stat))
		t->last_exit_stat = WEXITSTATUS(stat);
	return;
free:
	perror(t->shell);
	free_array(t->argv);
	free(t->cmd);
	exit(EXIT_FAILURE);
}

/**
 * handler_sigint - signal handler
 * @sg: input
 */

void handler_sigint(int sg)
{
	(void)sg;
	exit(EXIT_FAILURE);
}

/**
 * exec - exectute command
 * @t: data
 */

void exec(data *t)
{
	const char prmpt[] = PROMPT;

	signal(SIGINT, handler_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf(prmpt);

		read_cmd(t);
		if (_strlen(t->cmd) != 0)
		{
			split(t, " ");
			if (!exec_create(t))
			{
				_how(t);
				if (access(t->argv[0], F_OK) == 0)
				{
					perror(t->shell);
					start(t);
				}
				else
				{
					_printf(t->shell);
					_printf(": command not found: ");
					_printf(t->argv[0]);
					_printf("\n");
				}
			}
			free_array(t->argv);
		}
		free(t->cmd);
	}
}
