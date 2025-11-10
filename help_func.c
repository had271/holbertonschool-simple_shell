#include "main.h"

/**
 * _getenv - function to get an enviroment variable
 * @name: pointer
 * Return: pointer
*/

char *_getenv(const char *name)
{
	size_t name_len;
	char **env;
	char *entry;

	if (name == NULL)
	{
		return (NULL);
	}
	name_len = _strlen(name);
	for (env = environ; env && *env; env++)
	{
		entry = *env;
		if (_strncmp(entry, name, (int)name_len) == 0 && entry[name_len] == '=')
		{
			char *value = entry + name_len + 1;
			char *ret = malloc(_strlen(value) + 1);
			if (!ret)
			{
				perror("malloc");
				return (NULL);
			}
			_strcpy(ret, value);
			return (ret);
		}
	}
	return (NULL);
}
/**
 * _getchar - function to get a character from STDIN
 * Return: the character
*/

int _getchar(void)
{
	char b;
	ssize_t r;

	r = read(STDIN_FILENO, &b, 1);
	if (r <= 0)
		return (EOF);
	return ((unsigned char)b);
}

/**
 * _getline - getline function
 * @line: pointer
 * @line_size: pointer
 * @stream: pointer
 * Return: number of characters
*/

ssize_t _getline(char **linep, ssize_t *line_size, FILE *stream)
{
	char *buffer;
	ssize_t chars = 0;
	ssize_t size;

	if (!linep || !line_size || !stream)
		return (-1);
	size = *line_size;
	if (size <= 0) size = 32;
	buffer = malloc(size);
	if (!buffer)
	{
		perror("malloc");
		return (-1);
	}
	while (1)
	{
		int c = _getchar();
		if (c == EOF)
		{
			if (chars == 0)
			{
				free(buffer);
				return (-1);
			}
			buffer[chars] = '\0';
			break;
		}
		if (c == '\n')
		{
			buffer[chars] = '\0';
			break;
		}
		buffer[chars++] = (char)c;
		if (chars >= size)
		{
			ssize_t old_size = size;
			size += 32;
			buffer = _realloc(buffer, (unsigned int)old_size, (unsigned int)size);
			if (!buffer)
			{
				perror("realloc");
				return (-1);
			}
		}
	}
	*linep = buffer;
	*line_size = size;
	return (chars);
}

/**
  * _realloc -  function to realloc space of memory
  * @ptr: pointer
  * @old_size: size
  * @new_size: size
  * Return: new string
  */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *tmp;
	char *old_ptr;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	tmp = malloc(new_size);
	if (tmp == NULL)
		return (NULL);
	old_ptr = (char *)ptr;
	for (i = 0; i < old_size && i < new_size; i++)
		tmp[i] = old_ptr[i];
	free(ptr);
	return (tmp);
}
	

/**
 * free_double_pointer - function to free a pointer
 * @directories: pointer
*/

void free_double_pointer(char **dirs)
{
	if (!dirs)
		return;
	for (int i = 0; dirs[i]; i++)
		free(dirs[i]);
	free(dirs);
}




