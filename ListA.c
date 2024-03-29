#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * This function counts the number of nodes in the linked list.
 *
 * Return: Size of the linked list.
 */
size_t list_len(const list_t *h)
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
 * list_to_strings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node.
 *
 * This function takes a linked list of strings and converts it into an array
 * of strings.
 *
 * Return: An array of strings or NULL on failure.
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t i = list_len(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }

    strs[i] = NULL;
    return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * This function prints the elements of the linked list, including node numbers.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * node_starts_with - Finds a node whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: Prefix string to match.
 * @c: The next character after the prefix to match (-1 to ignore).
 *
 * This function searches for a node in the linked list whose string starts
 * with the specified prefix and, optionally, the next character after the
 * prefix.
 *
 * Return: A pointer to the matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }

    return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * This function retrieves the index (position) of a node in the linked list.
 *
 * Return: The index of the node or -1 if the node is not found in the list.
 */
ssize_t get_node_index(list_t *head, list_t *node)
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
