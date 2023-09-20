#include "shell.h"

/**
 * _strncpy - Copy a portion of a string to another string.
 * @dest: The destination string to copy to.
 * @src: The source string to copy from.
 * @n: The maximum number of characters to copy.
 *
 * This function copies up to 'n' characters from the 'src' string to the 'dest'
 * string. It returns a pointer to the 'dest' string.
 *
 * Return: A pointer to the 'dest' string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return (s);
}

/**
 * _strncat - Concatenate two strings up to a specified number of bytes.
 * @dest: The destination string to concatenate to.
 * @src: The source string to concatenate from.
 * @n: The maximum number of bytes to concatenate.
 *
 * This function concatenates up to 'n' bytes from the 'src' string to the 'dest'
 * string. It returns a pointer to the 'dest' string.
 *
 * Return: A pointer to the 'dest' string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0';
    return (s);
}

/**
 * _strchr - Locate the first occurrence of a character in a string.
 * @s: The string to search within.
 * @c: The character to look for.
 *
 * This function searches for the first occurrence of the character 'c' in the
 * string 's' and returns a pointer to the first matching character in 's'.
 * If 'c' is not found, it returns NULL.
 *
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    do {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);
}
