#include "shell.h"

/**
 * ench_get - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **ench_get(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = chan_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * set_envun - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int set_envun(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_nd_in(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * liverg_set - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int liverg_set(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_lenght(var) + str_lenght(value) + 2);
	if (!buf)
		return (1);
	copy_st(buf, var);
	cat_st(buf, "=");
	cat_st(buf, value);
	node = info->env;
	while (node)
	{
		p = begin(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	enad_notr(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
