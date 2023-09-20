#include "shell.h"

/**
 * _strlen - Calculate the length of a string.
 * @s: The string to measure.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/**
 * _strcmp - Compare two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if the strings are equal, a positive value if s1 > s2,
 *         or a negative value if s1 < s2.
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check if a string starts with a specified substring.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: A pointer to the next character after the found substring or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source buffer to append.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}
