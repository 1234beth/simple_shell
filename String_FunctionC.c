#include "shel.h"

/**
 **_Strrncpy - coPies the string
 *@dest:  destination striNg tO be copied into
 *@src:  soUrce strIng
 *@a:  aMount of characters to copy
 *Return: concatEnated stRing
 */
char *_Strrncpy(char *dest, char *src, int a)
{
	int i, j;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < a - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < a)
	{
		i = j;
		while (i < a)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (s);
}

/**
 **_Strrncat - concatenates two strings
 *@dest:  First striNg
 *@src:  seCond String
 *@a:  aMount of byTes to  maXimally use
 *Return: cOncatenAted strinG
 */
char *_Strrncat(char *dest, char *src, int a)
{
	int i, j;
	char *s = dest;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0' && i < a)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	if (i < a)
		dest[j] = '\0';
	return (s);
}

/**
 **_Strrchr - locates the chAracter in  string
 *@s: the stRing to  parse
 *@b:  chAracter to Look for
 *Return: (s) a poinTer to Memory area s
 */
char *_Strrchr(char *s, char b)
{
	do {
		if (*s == b)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
