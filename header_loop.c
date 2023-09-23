#include "shell.h"

/**
 * hsh - Main shell loop
 * @info: The parameter & return info struct
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or an error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_rgef(info);
		if (inter_active(info))
			put_st("$ ");
		_charputs(BUF_FLUSH);
		r = rginp_get(info);
		if (r != -1)
		{
			in_forgst(info, av);
			builtin_ret = builtin_finder(info);
			if (builtin_ret == -1)
				comand_find(info);
		}
		else if (inter_active(info))
			putrg_str('\n');
		avail_inf(info, 0);
	}
	his_fgwrite(info);
	avail_inf(info, 1);
	if (!inter_active(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_finder - Finds a builtin command
 * @info: The parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit()
 */
int builtin_finder(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", scaprg},
		{"env", myst_en},
		{"help", hand_st},
		{"history", title_my},
		{"setenv", stenv_mys},
		{"unsetenv", myrt_enven},
		{"cd", cmdrt_my},
		{"alias", alias_chat},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_computed(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * comand_find - Finds a command in PATH
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void comand_find(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delim_is(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, envst_get(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmd_fork(info);
	}
	else
	{
		if ((inter_active(info) || envst_get(info, "PATH=")
					|| info->argv[0][0] == '/') && command_is(info, info->argv[0]))
			cmd_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			err_rg(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - Forks an exec thread to run cmd
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void cmd_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, ench_get(info)) == -1)
		{
			avail_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				err_rg(info, "Permission denied\n");
		}
	}
}

