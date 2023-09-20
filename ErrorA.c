#include "shell.h"

/**
 * _eputs - Write a null-terminated string to the standard error (stderr).
 * @str: The string to be printed.
 *
 * This function iterates through the characters in the input string and writes
 * them one by one to the standard error stream (stderr).
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - Write a single character to the standard error (stderr).
 * @c: The character to be written.
 *
 * This function writes the specified character to the standard error stream
 * (stderr). It uses an internal buffer to accumulate characters before
 * flushing to minimize system calls.
 *
 * Return: On success, 1 is returned. On error, -1 is returned, and errno is set.
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        if (write(2, buf, i) == -1)
            return (-1);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putfd - Write a single character to the specified file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * This function writes the specified character to the provided file descriptor.
 * It uses an internal buffer to accumulate characters before flushing to
 * minimize system calls.
 *
 * Return: On success, 1 is returned. On error, -1 is returned, and errno is set.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        if (write(fd, buf, i) == -1)
            return (-1);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putsfd - Write a null-terminated string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function iterates through the characters in the input string and uses
 * `_putfd` to write them to the specified file descriptor. It returns the
 * number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += _putfd(*str++, fd);
    }
    return (i);
}
