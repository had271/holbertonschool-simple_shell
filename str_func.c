#include "main.h"

/**
*_strcat - function that concatenate strings
*@dest: name of the first pointer
*@src: name of the second pointer
*Return: pointer that points to the memory address where is the value of dest
*/

char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i + j] = src[j];
	}
		dest[i + j] = '\0';
return (dest);
}
