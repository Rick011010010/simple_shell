#include "shell.h"

/**
 * myst_en - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myst_en(info_t *info)
{
	ls_printdf(info->env);
	return (0);
}

/**
 * envst_get - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *envst_get(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * stenv_mys - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int stenv_mys(info_t *info)
{
	if (info->argc != 3)
	{
		_input("Incorrect number of arguements\n");
		return (1);
	}
	if (liverg_set(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myrt_enven - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myrt_enven(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_input("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		set_envun(info, info->argv[i]);

	return (0);
}

/**
 * listpop_env - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int listpop_env(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		enad_notr(&node, environ[i], 0);
	info->env = node;
	return (0);
}
