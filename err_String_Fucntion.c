#include "shel.h"

/**
 *_Eputs - prinT the input string
 * @str: the string to  Print
 *
 * Return: Nothing
 */
void _Eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _Eputchar - write  chracter b To stderr
 * @b: The charater to prinT
 *
 * Return: On succEss 1.
 * On error, -1 is rEturned, and errrno is Set appopriately.
 */
int _Eputchar(char b)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buf[j++] = b;
	return (1);
}

/**
 * _Putfd - write charActer c  given fd
 * @b:  charater to Print
 * @fd: The filedesciptor to write into
 *
 * Return: On succEss 1.
 * On error, -1 is reTurned, and errno is set apropriately.
 */
int _Putfd(char b, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buf[j++] = b;
	return (1);
}

/**
 *_Putsfd - prInt an inPut string
 * @str:  String to be print
 * @fb: the filedescripor to write to
 *
 * Return: number Of chArs put
 */
int _Putsfd(char *str, int fb)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _Putfd(*str++, fb);
	}
	return (j);
}
