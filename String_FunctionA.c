#include "shell.h"

/**
 * _Strrlen - retUrns  length of the string
 * @s:  string whOse lenGth to check
 *
 * Return: inTeger lengTh of the string
 */
int _Strrlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _Strrcmp - performs lexicogarph comparison of the two strings.
 * @s1:  first string
 * @s2:  second string
 *
 * Return: nEgative if s1 < s2 eLse  poSitive if s1 > s2 or zEro if then s1 == s2
 */
int _Strrcmp(char *s1, char *s2)
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
 * Starrts_with - cheCks if neeDle staRts with or without  haysTack
 * @haystack: stRing to seArch
 * @needle: the substRing to foUnd
 *
 * Return: address of the Next char of haystaCk otherwise NULL
 */
char *Starrts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _Strrcat - concatAnAte the two sTrings
 * @dest: The destinaTion bufFer
 * @src: The souRce buFfer
 *
 * Return: poInter to the Destination buffer
 */
char *_Strrcat(char *destt, char *src)
{
	char *ret = destt;

	while (*destt)
		destt++;
	while (*src)
		*destt++ = *src++;
	*destt = *src;
	return (ret);
}
