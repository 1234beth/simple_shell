#include "shel.h"

/**
 * bffree - frees  Pointer and NULLs  Address
 * @ptr: addreSs of poinTer to free
 *
 * Return: 1 if free, otherwise return 0.
 */
int bffree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
