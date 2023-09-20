#include "shell.h"

/**
 * string_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The integer value if conversion is successful, -1 on error.
 */
int string_to_int(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_error_message - Prints an error message to standard error.
 * @info: Pointer to a struct containing shell information.
 * @error_type: The string containing the specified error type.
 *
 * Return: Nothing.
 */
void print_error_message(info_t *info, char *error_type)
{
    _eputs(info->fname);
    _eputs(": ");
    print_decimal(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(error_type);
}

/**
 * print_decimal - Prints a decimal (integer) number to the specified file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
    int (*output_char)(char) = _putchar;
    int i, count = 0;
    unsigned int abs_value, current;

    if (fd == STDERR_FILENO)
        output_char = _eputchar;

    if (input < 0)
    {
        abs_value = -input;
        output_char('-');
        count++;
    }
    else
    {
        abs_value = input;
    }
    
    current = abs_value;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (abs_value / i)
        {
            output_char('0' + current / i);
            count++;
        }
        current %= i;
    }
    
    output_char('0' + current);
    count++;

    return (count);
}

/**
 * convert_to_string - Converts a number to a string.
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Flags for conversion (CONVERT_UNSIGNED, CONVERT_LOWERCASE, etc.).
 *
 * Return: A string representation of the number.
 */
char *convert_to_string(long int num, int base, int flags)
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

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0' in a string.
 * @buf: The address of the string to modify.
 *
 * Return: Nothing.
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
