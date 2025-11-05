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

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *tmp;
	unsigned int i;

	if (new_size == old_size)
	return (ptr);
	if (ptr == NULL)
	{
	tmp = malloc(new_size);
	if (tmp == NULL)
	return (NULL);
	return (tmp);
	}
	if ((new_size == 0) && (ptr != NULL))
	{
	free(ptr);
	return (NULL);
	}
	if (new_size > old_size)
	{
	tmp = malloc(new_size);
	if (tmp == NULL)
	return (NULL);
	for (i = 0; i < old_size; i++)
	((char *)tmp)[i] = ((char *)ptr)[i];
	free(ptr);
	return (tmp);
	}
	else
	{
	tmp = malloc(new_size);
	if (tmp == NULL)
	return (NULL);
	for (i = 0; i < new_size; i++)
	{
	((char *)tmp)[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (tmp);
	}
	return (NULL);
}
