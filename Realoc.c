/**
 * _memset - Fills a block of memory with a specified byte.
 * @s: Pointer to the memory area to be filled.
 * @b: The byte value to fill the memory with.
 * @n: The number of bytes to be filled.
 *
 * This function sets the first 'n' bytes of the memory pointed to by 's' to the
 * specified byte 'b'. It is commonly used to initialize or reset memory buffers.
 *
 * Return: A pointer to the memory area 's'.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;
    return (s);
}

/**
 * ffree - Frees an array of strings and the array itself.
 * @pp: Pointer to the array of strings to be freed.
 *
 * This function releases the memory occupied by each individual string in the
 * array 'pp' and then frees the memory used by the array itself. It is commonly
 * used to deallocate memory associated with a dynamically allocated string array.
 */
void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;
    while (*pp)
        free(*pp++);
    free(a);
}

/**
 * _realloc - Reallocates a block of memory to a new size.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: The original size (in bytes) of the memory block.
 * @new_size: The new size (in bytes) for the memory block.
 *
 * This function changes the size of the memory block pointed to by 'ptr' to
 * 'new_size' bytes. It returns a pointer to the reallocated memory. If the new
 * size is larger, the additional memory is uninitialized. If the new size is
 * smaller, data may be truncated. If 'ptr' is NULL, it behaves like malloc.
 *
 * Return: A pointer to the reallocated memory block, or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return (malloc(new_size));
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return (ptr);

    p = malloc(new_size);
    if (!p)
        return (NULL);

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return (p);
}
