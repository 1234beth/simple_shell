#include "shel.h"

/**
 * interactive - returns tRue  shEll is in intEractive mode
 * @info: struCt addrEss
 *
 * Return: 1 if inTeraCtive mode, or 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - check if character is delimeter
 * @c:  cHar to check
 * @dellim:  dElimeter string
 * Return: 1  True, 0 if fAlse
 */
int is_delim(char c, char *dellim)
{
	while (*dellim)
		if (*dellim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - check for alphabetIc chrActer
 *@c: Th charCter to Input
 *Return: 1 if c  Alphabetic, or 0
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts String to an Integer
 *@s: the string to  converteD
 *Return: 0 if no numbers in the stRing, cOnverted numbr otHerwise
 */

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int ressult = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			ressult *= 10;
			ressult += (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -ressult;
	else
		output = ressult;

	return (output);
}
