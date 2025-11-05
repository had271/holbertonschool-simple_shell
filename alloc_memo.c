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
	* _realloc -  function to realloc space of memory
	* @ptr: pointer holding what we want to realloc
	* @old_size: size of the first string
	* @new_size: size of the new string
	* Return: new string
	*/
