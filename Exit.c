#include "shell.h"

/**
 * copy_string - Copies a string up to a specified length.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *copy_string(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

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
    return result;
}

/**
 * concatenate_strings - Concatenates two strings up to a specified length.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to use.
 *
 * Return: A pointer to the concatenated string.
 */
char *concatenate_strings(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

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
    return result;
}

/**
 * find_character - Locates the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *find_character(char *s, char c)
{
    do
    {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}
