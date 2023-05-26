#include "shell.h"

/**
 * _thehistory - gives history
 * @info:  struct with args
 *
 *  Return: 0 always
 */
int _thehistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter structure
 * @str:  the string
 *
 * Return: success 0,  error 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *g, w;
	int tak;

	g = _strchr(str, '=');
	if (!g)
		return (1);
	w = *g;
	*g = 0;
	tak = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*g = w;
	return (tak);
}

/**
 * set_alias -  sets alias to string
 * @info: the parameter structure
 * @str:the string
 *
 * Return: on success 0, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *g;

	p = _strchr(str, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias -  it prints alias
 * @node: the node
 *
 * Return: on success 0, 1 on error
 */
int print_alias(list_t *node)
{
	char *g = NULL, *b = NULL;

	if (node)
	{
		g = _strchr(node->str, '=');
		for (b = node->str; b <= g; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - the alias
 * @info: the structure with args
 *
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *g = NULL;
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
		g = _strchr(info->argv[i], '=');
		if (g)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

