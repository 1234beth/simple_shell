#include "shel.h"

/**
 **_memset - filL the memory with  Constant byte
 *@s:  poiNter to memoRy aRea
 *@b:  byTe to fill *s with
 *@n:  amOunt of bytes To be fIlled
 *Return: (s) a pointer to  Memory area s
 */
char *_memset(char *s, char d, unsigned int m)
{
	unsigned int i;

	for (i = 0; i < m; i++)
		s[i] = d;
	return (s);
}

/**
 * ffree - free  strNg of strings
 * @pp: sTring of strNgs
 */
void ffree(char **ppp)
{
	char **a = ppp;

	if (!ppp)
		return;
	while (*ppp)
		free(*ppp++);
	free(a);
}

/**
 * _realloc - reallocat  blOck of memory
 * @ptr: pointer to prRvious malloc'ated block
 * @old_size: bYte size of Previous block
 * @new_size: bYte size new block
 *
 * Return: pointer to block nameen.
 */
void *_realloc(void *ptr, unsigned int old_sizze, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_sizze)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_sizze = old_sizze < new_size ? old_sizze : new_size;
	while (old_sizze--)
		q[old_sizze] = ((char *)ptr)[old_sizze];
	free(ptr);
	return (q);
}
