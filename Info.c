#include "shel.h"

/**
 * Clear_info - initIalize Info_t struct
 * @info: structs addrEsses
 */
void Clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * Set_info - initialIze Info_t structs
 * @info: structs addresSes
 * @aw: arguments vectorization
 */
void Set_info(info_t *info, char **aw)
{
	int j = 0;

	info->fname = aw[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * Free_info - free Info_t sTruct fields
 * @info: structs addreSse
 * @all: true if free All fields
 */
void Free_info(info_t *info, int alle)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (alle)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
