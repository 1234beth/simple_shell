#include "shell.h"

/**
 * input_buf - Buffer and process chained commands from input.
 * @info: Pointer to the parameter struct.
 * @buf: Pointer to the address of the input buffer.
 * @len: Pointer to the length of the input buffer.
 *
 * This function reads input from the user, buffering chained commands
 * terminated by semicolons (';'). It handles command chaining by returning
 * individual commands from the buffer on each call.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* Remove trailing newline */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
 * get_input - Get the next line of input from the user.
 * @info: Pointer to the parameter struct.
 *
 * This function handles processing of chained commands and returns individual
 * commands from the buffer on each call. It also handles command chaining by
 * returning the current command and updating the buffer position.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len) /* We have commands left in the chain buffer */
    {
        j = i; /* Initialize new iterator to the current buffer position */
        p = buf + i; /* Get pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* Iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* Increment past nulled semicolon */
        if (i >= len) /* Reached end of buffer? */
        {
            i = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back pointer to current command position */
        return (_strlen(p)); /* Return length of current command */
    }

    *buf_p = buf; /* Not a chain; pass back buffer from _getline() */
    return (r); /* Return length of buffer from _getline() */
}

/**
 * read_buf - Read data into a buffer from a file descriptor.
 * @info: Pointer to the parameter struct.
 * @buf: The buffer to read into.
 * @i: Pointer to the size of the buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

/**
 * _getline - Get the next line of input from STDIN.
 * @info: Pointer to the parameter struct.
 * @ptr: Pointer to the address of the buffer (preallocated or NULL).
 * @length: Pointer to the size of the preallocated buffer (if not NULL).
 *
 * Return: The number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * sigintHandler - Signal handler to block Ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
