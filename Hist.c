#include "shell.h"

/**
 * getShellHistoryFile - Gets the shell history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *getShellHistoryFile(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

/**
 * writeShellHistory - Creates a file or appends to an existing file for shell history.
 * @info: The parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int writeShellHistory(info_t *info)
{
    ssize_t fd;
    char *filename = getShellHistoryFile(info);
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
 * readShellHistory - Reads shell history from a file.
 * @info: The parameter struct.
 *
 * Return: The number of history entries read or 0 on failure.
 */
int readShellHistory(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = getShellHistoryFile(info);

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
    buf[fsize] = 0;
    if (rdlen <= 0)
        return (free(buf), 0);
    close(fd);
    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            buildShellHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    if (last != i)
        buildShellHistoryList(info, buf + last, linecount++);
    free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);
    renumberShellHistory(info);
    return (info->histcount);
}

/**
 * buildShellHistoryList - Adds an entry to the shell history linked list.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @linecount: The history line count, histcount.
 *
 * Return: Always 0.
 */
int buildShellHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;
    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;
    return (0);
}

/**
 * renumberShellHistory - Renumbers the shell history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
 */
int renumberShellHistory(info_t *info)
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
