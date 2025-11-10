#include "main.h"

/**
*_strcat - function that concatenate strings
*@dest: name of the first pointer
*@src: name of the second pointer
*Return: pointer
*/

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j;

	if (!dest || !src)
		return (dest);
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

/**
*_strcmp - function to compare two strings
*@s1: pointer
*@s2: pointer
*Return: integer
*/

int _strcmp(char *s1, char *s2)
{
	int i;
	int compare;

	if (!s1 || !s2)
		return (s1 ? 1 : (s2 ? -1 : 0));
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			compare = (s1[i] - s2[i]);
			return (compare);
		}
			i++;
	}
compare = (s1[i] - s2[i]);
return (compare);
}

/**
*_strcpy - function to copy string
*@dest: pointer
*@src: pointer
*Return: pointer
*/

char *_strcpy(char *dest, char *src)
{
	unsigned int i;

	if (!dest || !src)
		return (dest);
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
		dest[i] = '\0';
return (dest);
}

/**
*_strlen - Return the lenght of a string
*@s: pointer
*Return: lenght
*/

size_t _strlen(const char *s)
{
	size_t len = 0;

	while (s && *s)
	{
		s++;
		len++;
	}
	return (len);
}


/**
 * _strncmp - function to compare strings
 * @s1: string 1
 * @s2: string 2
 * @n: index
 * Return: result
*/

int _strncmp(const char *s1, const char *s2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
			break;
	}
return (0);
}

