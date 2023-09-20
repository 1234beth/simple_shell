#include "shell.h"

/**
 * _myhistory - Display the command history list with line numbers.
 * @info: Pointer to the info_t structure.
 *
 * This function prints the command history list, displaying each command
 * with its line number, starting at 0.
 *
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Unset (remove) an alias.
 * @info: Pointer to the info_t structure.
 * @str: The string representing the alias.
 *
 * This function unsets (removes) an alias specified by the input string 'str'.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - Set an alias to a string.
 * @info: Pointer to the info_t structure.
 * @str: The string representing the alias.
 *
 * This function sets an alias specified by the input string 'str'.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node to print.
 *
 * This function prints an alias node in the format 'alias='string''.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - Manage shell aliases.
 * @info: Pointer to the info_t structure.
 *
 * This function mimics the behavior of the 'alias' built-in command (man alias).
 * It allows setting and printing aliases for the shell.
 *
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
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
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
