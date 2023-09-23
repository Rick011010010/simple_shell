#include "shell.h"

/**
 * long_strze - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t long_strze(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * chan_to_str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **chan_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = long_strze(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_lenght(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_st(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * lesta_at_pint - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t lesta_at_pint(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_st(revert_num(h->num, 10, 0));
		putrg_str(':');
		putrg_str(' ');
		put_st(h->str ? h->str : "(nil)");
		put_st("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * bestr_nd - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *bestr_nd(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begin(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * in_deffer - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t in_deffer(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
