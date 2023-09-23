#include "shell.h"

/**
 * getdf_all - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getdf_all(info_t *info)
{
	char *buf, *dir;

	dir = envst_get(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_lenght(dir) + str_lenght(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_st(buf, dir);
	cat_st(buf, "/");
	cat_st(buf, HIST_FILE);
	return (buf);
}

/**
 * his_fgwrite - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int his_fgwrite(info_t *info)
{
	ssize_t fd;
	char *filename = getdf_all(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_inputsrg(node->str, fd);
		_rgputs('\n', fd);
	}
	_rgputs(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * his_rd - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int his_rd(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getdf_all(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			bui_ls_his(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		bui_ls_his(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_nd_in(&(info->history), 0);
	renth_tr(info);
	return (info->histcount);
}

/**
 * bui_ls_his - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int bui_ls_his(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	enad_notr(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renth_tr - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renth_tr(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
