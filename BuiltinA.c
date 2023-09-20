#include "shell.h"

/**
 * display_command_history - Displays the command history list, each command
 *                           preceded by line numbers.
 * @info: Pointer to a struct containing shell information.
 * 
 * Return: Always returns 0.
 */
int display_command_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Unsets (removes) an alias.
 * @info: Pointer to a struct containing shell information.
 * @str: The alias string to unset.
 * 
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equals_sign, saved_char;
    int unset_result;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return (1);

    saved_char = *equals_sign;
    *equals_sign = '\0';

    unset_result = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

    *equals_sign = saved_char;

    return (unset_result);
}

/**
 * set_alias - Sets or updates an alias.
 * @info: Pointer to a struct containing shell information.
 * @str: The alias string to set or update.
 * 
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *equals_sign;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return (1);

    if (!*++equals_sign)
        return (unset_alias(info, str));

    unset_alias(info, str);

    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node to print.
 * 
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *equals_sign, *alias;

    if (node)
    {
        equals_sign = _strchr(node->str, '=');
        for (alias = node->str; alias <= equals_sign; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(equals_sign + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * manage_aliases - Manages shell aliases.
 * @info: Pointer to a struct containing shell information.
 * 
 * Return: Always returns 0.
 */
int manage_aliases(info_t *info)
{
    int i = 0;
    char *equals_sign;
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
        equals_sign = _strchr(info->argv[i], '=');
        if (equals_sign)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
