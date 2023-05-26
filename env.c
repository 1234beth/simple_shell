#include "shell.h"

/**
 * _env -   prints current env
 * @info: struct with args
 *
 * Return: Always 0
 */
int _env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info:  struct arguments. 
 * @ename: env name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *ename)
{
	list_t *node = info->env;
	char *g;

	while (node)
	{
		g = starts_with(node->str, ename);
		if (g && *g)
			return (g);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv -  it Initialize/modify a new or existing env variable           
 * @info: struct with arguments.
 *
 *  Return: Always 0
 */
int _setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Args num\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv -  remove an env variable
 * @info: struct with args
 *
 * Return: Always 0
 */
int _unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_puts("minimal args.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: struct with arguments
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; envr[i]; i++)
		add_node_end(&node, envr[i], 0);
	info->env = node;
	return (0);
}

