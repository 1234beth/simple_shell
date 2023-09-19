#include "shel.h"

/**
 * _Myenv - print  cUrrent enVironment
 * @info: Structure containinG sny  argUments. UseD to maintain
 *          constant function protoType.
 * Return: Always be 0
 */
int _Myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _Getenv - get value of  EnvIron variable
 * @info: Structure contaIn pOtential arguments. uSe to Maintain
 * @names: eNv var nAme
 *
 * Return: the value of that
 */
char *_Getenv(info_t *info, const char *names)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, names);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}


/**
 * Populate_env_list - Populates envir liNked list
 * @info: Structure containiNg potential Arguments. UsEd to maintain
 *          constant fuCtion prototyPing.
 * Return: Always be 0 pls
 */
int Populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
