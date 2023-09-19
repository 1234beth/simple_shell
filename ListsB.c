#include "shel.h"

/**
 * List_len - determine Length of the Linked list
 * @h: pointer to the fiRst noDe
 *
 * Return: size of List
 */
size_t List_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * List_to_strings - retuRns array of the strings of list->str
 * @head: pointEr to firSt nodE
 *
 * Return: array of strings
 */
char **List_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), i;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < j; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * print_List - prints elements of the list_t linked list
 * @h: pointer to firSt nodE
 *
 * Return: size of liSt
 */
size_t print_List(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * Node_starts_with - return the node Whose stRing sTarts with prefix
 * @node: pointer to the lisT heaD
 * @prefix: string to maTch
 * @b: the next characteR afteR prfix to match
 *
 * Return: match noDe or nuLl
 */
List_t *node_starts_with(list_t *node, char *prefix, char b)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((b == -1) || (*p == b)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_Node_index - gets the index of a nodE
 * @head: ponter to the List head
 * @node: poInter to  Node
 *
 * Return: index oF Node or -1
 */
ssize_t get_Node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
