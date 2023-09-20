#include "shell.h"

/**
 * get_environ - Retrieve a copy of the environment variables.
 * @info: Pointer to the parameter struct.
 *
 * This function returns a string array copy of the shell's environment
 * variables. If the environment has changed or is not yet stored, it
 * updates and retrieves the latest version.
 *
 * Return: A string array representing the environment variables.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Pointer to the parameter struct.
 * @var: The string representing the environment variable to remove.
 *
 * This function removes an environment variable specified by the "var"
 * parameter from the environment list. It returns 1 if the variable is
 * successfully deleted, or 0 if it does not exist.
 *
 * Return: 1 if the environment variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
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
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to the parameter struct.
 * @var: The string representing the environment variable name.
 * @value: The string representing the environment variable value.
 *
 * This function initializes a new environment variable or modifies an
 * existing one with the provided name and value. If the variable already
 * exists, it updates the value. If it doesn't exist, it creates a new
 * environment variable.
 *
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}
