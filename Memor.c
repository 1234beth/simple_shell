/**
 * bfree - Frees memory and sets a pointer to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function checks if the provided pointer is not NULL, and if so, it frees
 * the memory associated with it using the `free` function. Afterward, it sets
 * the pointer itself to NULL, ensuring that it no longer points to the freed memory.
 *
 * @return: Returns 1 if the memory was successfully freed and the pointer set to NULL,
 *          Returns 0 if the pointer was already NULL or not provided.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);    // Free the memory if the pointer is not NULL.
        *ptr = NULL;   // Set the pointer to NULL to prevent further access.
        return 1;       // Indicate successful memory release.
    }
    return 0;           // Indicate that no action was taken (pointer was NULL).
}
