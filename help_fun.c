#include "main.h"

/**
 * _strcmp - compares two strings
 * @s1: pointer 1
 * @s2: pointer 2
 * Return: result
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/**
 * _strcpy - function that copies the string pointed to by src
 * @dest: pointer
 * @src: ponter
 * Return: @dest
 */
char *_strcpy(char *dest, char *src)
{
	char *c = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (c);
}

/**
 * _split - split string
 * @str: string
 * @sep: separator
 * Return: divided path
 */

char **_split(char *str, char *sep)
{
    char **split_str;
    int i = 0, j = 0, start = 0, k = 0;

    split_str = _calloc(100, sizeof(char *));
    if (!split_str)
        return (NULL);

    while (str[i] != '\0')
    {
        for (j = 0; sep[j] != '\0'; j++)
        {
            if (str[i] == sep[j])
            {
                i++;
                start = i;
                j = -1;
            }
        }

        while (str[i] != '\0')
        {
            for (j = 0; sep[j] != '\0'; j++)
                if (str[i] == sep[j])
                    break;
            if (sep[j] != '\0')
                break;
            i++;
        }

        if (i > start)
        {
            str[i] = '\0';
            split_str[k++] = &str[start];
            i++;
            start = i;
        }
    }
	split_str[k] = NULL;
    return (split_str);
}


/**
 * _strcat - function that concatenates two strings
 * @dest: string
 * @src: string
 * Return: @dest
 */

char *_strcat(char *dest, char *src)
{
	int a, b;

	for (a = 0; dest[a] != '\0'; a += 1)
	{}

	for (b = 0; src[b] != '\0'; b += 1)
	{
		dest[a] = src[b];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

/**
 * _strlen - string length
 * @s: string
 * Return: result
 *
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return (i);
}
