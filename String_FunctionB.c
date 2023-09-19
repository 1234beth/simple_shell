#include "shel.h"

/**
 * _Strrcpy - copIes a string
 * @dest: the desTination
 * @src: the souRce of string
 *
 * Return: pointer to the destnAtion
 */
char *_Strrcpy(char *destt, char *src)
{
	int a = 0;

	if (destt == src || src == 0)
		return (destt);
	while (src[a])
	{
		destt[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (destt);
}

/**
 * _Strrdup - duplIcates the sTring
 * @str:  stRing to dupliCate
 *
 * Return: poInter to  dupLicated strIng
 */
char *_Strrdup(const char *str)
{
	int lengtth = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lengtth++;
	ret = malloc(sizeof(char) * (lengtth + 1));
	if (!ret)
		return (NULL);
	for (lengtth++; lengtth--;)
		ret[lengtth] = *--str;
	return (ret);
}

/**
 *_Puts - priNts tje iNput stRing
 *@str:  String to prinT
 *
 *
 * Return: 0
 */
void _Puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _Putcharr - wriTe character c to stdout
 * @c:  charcTer to print
 *
 * Return:  sUccess 1.
 * On error, -1 return , is set appropriately.
 */
int _Putcharr(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
