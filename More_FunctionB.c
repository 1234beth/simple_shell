#include "shell.h"

/**
 * _errratoi - convert strinG to an integer
 * @s: the string to  converT
 * Return: 0 if no numbErs iN string or converted numbeR
 *       -1 on error
 */
int _errratoi(char *s)
{
	int j = 0;
	unsigned long int ressult = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			ressult *= 10;
			ressult += (s[j] - '0');
			if (ressult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (ressult);
}

/**
 * Print_error - print  error message
 * @info: the parameteR and rEturn info on struct
 * @estrr: string contaiNing speciFied errOr type
 * Return: 0 if no numbErs in sTring, or converTed number
 *        -1 on errOr
 */
void Print_error(info_t *info, char *estrr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estrr);
}

/**
 * Print_d - function prints decimal (integer) number
 * @input: the inpuT
 * @fd: the file deScriptor to write to
 *
 * Return: number of characteRs printed
 */
int Print_d(int input, int fb)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fb == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * Convert_num - converTer function,  clone of itoa
 * @num: numBer
 * @base: baSe
 * @flags: argumnt flagS
 *
 * Return: sTring
 */
char *Convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char siggn = 0;
	char *ptr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		siggn = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % base];
		m /= base;
	} while (m != 0);

	if (siggn)
		*--ptr = siggn;
	return (ptr);
}

/**
 * Remove_comment - function rEplace first instanCe of '#' with '\0'
 * @buf: address of striNg to modifY
 *
 * Return: Always 0;
 */
void Remove_comment(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
