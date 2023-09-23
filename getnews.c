#include "shell.h"

/**
 * info_rgef - initializes info_t struct
 * @info: struct address
 */
void info_rgef(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * in_forgst - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void in_forgst(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = torg_st(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = double_st(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alstr_rep(info);
		rp_variables(info);
	}
}

/**
 * avail_inf - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void avail_inf(info_t *info, int all)
{
	frg_st(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			li_nd_free(&(info->env));
		if (info->history)
			li_nd_free(&(info->history));
		if (info->alias)
			li_nd_free(&(info->alias));
		frg_st(info->environ);
			info->environ = NULL;
		forfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		putrg_str(BUF_FLUSH);
	}
}
