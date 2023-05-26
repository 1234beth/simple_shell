/*task 6*/

#include "shell.h"

/**
 * _getline - reads the line
 * @lineptr: pointer to the buffer
 * @w: size of the buffer
 * @ky: file descriptor to read from
 *
 * Return: the number of characters read, or -1 on failure
 */

ssize_t _getline(char **lineptr, size_t *w, int ky)
{
	static char buffer[1024];
	static char *buf_pos;
	ssize_t n_rd = 0;
	ssize_t l_read = 0;

	if (!lineptr || !w)
		return (-1);

	if (*lineptr == NULL || *w == 0)
	{
		*w = 120;
		*lineptr = malloc(*w);

		if (!*lineptr)
			return (-1);
	}

	while ((n_rd = read(ky, buffer, 1024)) > 0)
	{
		for (ssize_t g = 0; g < n_rd; g++)
		{
			if (total_read >= *w - 1)
			{
				*w * = 2;
				*lineptr = realloc(*lineptr);
				if (!*lineptr)
					return (-1);

			}

			(*lineptr)[l_read++] = buffer[g];

			if (buffer[g] == '\n')
			{
				(*lineptr)[l_read] = '\0';
				return (l_read);
			}
		}

		buf_pos = buffer + n_rd;
	}
	if (n_rd == -1 || l_read == 0)
		return (-1);
	(*lineptr)[l_read] = '\0';

	return (l_read);
}
