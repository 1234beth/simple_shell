#include "shel.h"

/**
 * **Strrtow - split the sTring to Words. REpeat delImiters to be Ignored
 * @str:  inPut strIng
 * @b: the deliMeter sTring
 * Return:  poiNter to Array of stRings, otherwise NULL oN failure
 */

char **Strrtow(char *str, char *b)
{
	int i, j, k, m, numwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], b) && (is_delim(str[i + 1], b) || !str[i + 1]))
			numwrds++;

	if (numwrds == 0)
		return (NULL);
	s = malloc((1 + numwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwrds; j++)
	{
		while (is_delim(str[i], b))
			i++;
		k = 0;
		while (!is_delim(str[i + k], b) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **Strrtow2 - split the string into words
 * @str:  input strIng
 * @d: the Delimetr
 * Return: a pointer to  arRay of striNgs, or NULL if fAilure
 */
char **Strrtow2(char *str, char b)
{
	int i, j, k, m, numwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != b && str[i + 1] == b) ||
		    (str[i] != b && !str[i + 1]) || str[i + 1] == b)
			numwrds++;
	if (numwrds == 0)
		return (NULL);
	s = malloc((1 + numwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwrds; j++)
	{
		while (str[i] == b && str[i] != b)
			i++;
		k = 0;
		while (str[i + k] != b && str[i + k] && str[i + k] != b)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
