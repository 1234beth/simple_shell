#include "shell.h"

/**
 * _myenv - Display the current environment variables.
 * @info: Pointer to the info_t structure.
 *
 * This function prints the current environment variables in the format
 * "VAR=VALUE" for each variable.
 *
 * Return: Always returns 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Pointer to the info_t structure.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable if found, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv - Set or modify an environment variable.
 * @info: Pointer to the info_t structure.
 *
 * This function initializes a new environment variable or modifies an
 * existing one with the specified name and value.
 *
 * Return: Always returns 0.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Pointer to the info_t structure.
 *
 * This function removes one or more environment variables specified as
 * arguments. It checks the number of arguments to ensure they are provided.
 *
 * Return: Always returns 0.
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i < info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to the info_t structure.
 *
 * This function populates the environment linked list with the current
 * environment variables.
 *
 * Return: Always returns 0.
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
