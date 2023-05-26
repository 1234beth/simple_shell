/*task4*/
#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination to
 *@src: the source
 *@m: characters to be copied
 *
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int m)
{
	int l, w;
	char *s = dest;

	l = 0;
	while (src[l] != '\0' && l < m - 1)
	{
		dest[l] = src[l];
		l++;
	}
	if (l < m)
	{
		w = l;
		while (w < m)
		{
			dest[w] = '\0';
			w++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src:  second string
 *@m: the bytes used
 *
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int l, w;
	char *s = dest;

	l = 0;
	w = 0;
	while (dest[l] != '\0')
		l++;
	while (src[w] != '\0' && w < m)
	{
		dest[l] = src[w];
		l++;
		w++;
	}
	if (w < m)
		dest[l] = '\0';
	return (s);
}

/**
 **_strchr - string character
 *@s: the string
 *@c: character to look for
 *
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}


