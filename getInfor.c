#include "shell.h"

/**
 * initInfo - Initializes an info_t struct by setting its fields to NULL.
 * @info: Pointer to the info_t struct.
 */
void initInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * configureInfo - Initializes an info_t struct using the provided argument vector.
 * @info: Pointer to the info_t struct.
 * @av: Argument vector.
 */
void configureInfo(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
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
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replaceAlias(info);
        replaceVars(info);
    }
}

/**
 * cleanInfo - Frees the fields of an info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: True if all fields should be freed.
 */
void cleanInfo(info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            freeList(&(info->env));
        if (info->history)
            freeList(&(info->history));
        if (info->alias)
            freeList(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}
