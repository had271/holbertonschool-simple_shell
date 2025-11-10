#include "main.h"


/**
	* _calloc - function that allocates memory for an array, using malloc
	* @nmemb: array
	* @size: size
	* Return: pointer or NULL
	*/

void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned int index = 0;
	char *ptr = NULL;

	if (nmemb == 0 || size == 0)
	return (NULL);

	ptr = malloc(nmemb * size);

	if (ptr == NULL)
	return (NULL);

	for (; index < (nmemb * size); index++)
	ptr[index] = 0;

	return (ptr);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to old memory
 * @old_size: old size
 * @new_size: new size
 * Return: pointer to new memory or NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    unsigned int i;

    if (new_size == old_size)
        return (ptr);

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }

    if (ptr == NULL)
        return (malloc(new_size));

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return (NULL);

    for (i = 0; i < old_size && i < new_size; i++)
        new_ptr[i] = ((char *)ptr)[i];

    free(ptr);
    return (new_ptr);
}
