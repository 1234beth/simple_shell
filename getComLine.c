#include "shell.h"

/**
 * buffer_chained_commands - Buffers chained commands separated by semicolons.
 * @info: Pointer to the parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Return: Number of bytes read.
 */
ssize_t buffer_chained_commands(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        bytes_read = getline(buf, &len_p, stdin);
#else
        bytes_read = custom_getline(info, buf, &len_p);
#endif
        if (bytes_read > 0)
        {
            if ((*buf)[bytes_read - 1] == '\n')
            {
                (*buf)[bytes_read - 1] = '\0';
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            {
                *len = bytes_read;
                info->cmd_buf = buf;
            }
        }
    }
    return (bytes_read);
}

/**
 * get_input_line - Gets a line of input without the trailing newline character.
 * @info: Pointer to the parameter struct.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input_line(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t bytes_read = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytes_read = buffer_chained_commands(info, &buf, &len);
    if (bytes_read == -1)
        return (-1);

    if (len)
    {
        j = i;
        p = buf + i;

        check_chain(info, buf, &j, i, len);
        while (j < len)
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return (_strlen(p));
    }

    *buf_p = buf;
    return (bytes_read);
}

/**
 * read_buffer - Reads a buffer from the input file descriptor.
 * @info: Pointer to the parameter struct.
 * @buf: The buffer to read into.
 * @i: The size of the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
    ssize_t bytes_read = 0;

    if (*i)
        return (0);
    bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
    if (bytes_read >= 0)
        *i = bytes_read;
    return (bytes_read);
}

/**
 * custom_getline - Gets the next line of input from STDIN.
 * @info: Pointer to the parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        bytes_read = *length;
    if (i == len)
        i = len = 0;

    bytes_read = read_buffer(info, buf, &len);
    if (bytes_read == -1 || (bytes_read == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, bytes_read, bytes_read ? bytes_read + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (bytes_read)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    bytes_read += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = bytes_read;
    *ptr = p;
    return (bytes_read);
}

/**
 * sigintHandler - Blocks Ctrl-C and prints a new prompt.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
