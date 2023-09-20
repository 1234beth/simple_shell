#include "shell.h"

/**
 * get_history_file - Retrieve the path to the history file.
 * @info: Pointer to the parameter struct.
 *
 * This function constructs and returns the full path to the history file
 * based on the user's home directory and the predefined history file name.
 *
 * Return: A dynamically allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = '\0';
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

/**
 * write_history - Write the command history to a file.
 * @info: Pointer to the parameter struct.
 *
 * This function creates a file or appends to an existing history file and
 * writes the command history stored in the shell's history linked list to it.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * read_history - Read command history from a file.
 * @info: Pointer to the parameter struct.
 *
 * This function reads command history from a file and populates the shell's
 * history linked list with the retrieved commands.
 *
 * Return: The number of commands read from the history file or 0 on failure.
 */
int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (0);

    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0)
        return (free(buf), 0);

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        build_history_list(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);
    return (info->histcount);
}

/**
 * build_history_list - Add an entry to the history linked list.
 * @info: Pointer to the parameter struct.
 * @buf: The command buffer to add to the history.
 * @linecount: The line count or history count for the command.
 *
 * This function adds an entry to the shell's command history linked list,
 * including the provided command buffer and its associated line count.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Pointer to the parameter struct.
 *
 * This function renumbers the line counts of the commands in the history
 * linked list to ensure they are consecutive after changes (e.g., deletion).
 *
 * Return: The new history count.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}
