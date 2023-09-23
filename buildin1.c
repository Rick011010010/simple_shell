#include "shell.h"

/**
 * title_my - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int title_my(info_t *info)
{
	lesta_at_pint(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = chrfg_st(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_nd_in(&(info->alias),
		in_deffer(info->alias, bestr_nd(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = chrfg_st(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (enad_notr(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = chrfg_st(node->str, '=');
		for (a = node->str; a <= p; a++)
		putrg_str(*a);
		putrg_str('\'');
		put_st(p + 1);
		put_st("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_chat - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_chat(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = chrfg_st(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(bestr_nd(info->alias, info->argv[i], '='));
	}

	return (0);
}
