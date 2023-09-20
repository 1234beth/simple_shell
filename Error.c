#include "shell.h"

/**
 * _erratoi - Convert a string to an integer with error handling.
 * @s: The string to be converted.
 *
 * This function converts the input string 's' to an integer and returns
 * the result. It performs error checking to handle cases where the
 * conversion is not possible, returning -1 on error.
 *
 * Return: The converted integer if successful, or -1 on error.
 */
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;  /* Skip leading plus sign */
    for (i = 0;  s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1); // Overflow
        }
        else
            return (-1); // Invalid character
    }
    return (result);
}

/**
 * print_error - Print an error message.
 * @info: Pointer to the info_t structure.
 * @estr: String containing the specified error type.
 *
 * This function prints an error message to the standard error (stderr) stream,
 * including the filename, line number, and the specified error message.
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - Print a decimal (integer) number (base 10).
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to (stdout or stderr).
 *
 * This function prints a decimal (base 10) integer to the specified file
 * descriptor. It returns the number of characters printed.
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * convert_number - Convert a number to a string representation.
 * @num: The number to be converted.
 * @base: The base for conversion (e.g., 10 for decimal).
 * @flags: Conversion flags.
 *
 * This function converts a long integer 'num' to a string representation
 * in the specified base. It supports both signed and unsigned conversions,
 * and it returns a pointer to the resulting string.
 *
 * Return: A pointer to the converted string.
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * remove_comments - Replace the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 *
 * This function searches for the first instance of '#' in the input string 'buf'
 * and replaces it with a null terminator ('\0'). This effectively removes any
 * comments from the string.
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
