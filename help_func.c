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
}
/**
 * _getchar - function to get a character from STDIN
 * Return: the character
*/

int _getchar(void)
{
	char charbuf[1];
	int a;

	a = read(0, charbuf, 1);

	if (a < 1)
	perror("read failed");

return (charbuf[0]);
}

/**
 * _getline - getline function
 * @line: pointer
 * @line_size: pointer
 * @stream: pointer
 * Return: number of characters
*/

ssize_t _getline(char **line, ssize_t *line_size, FILE *stream)
{
	char *buffer;
	ssize_t chars = 0, character;

	buffer = malloc(sizeof(char) * (*line_size));

	if (!buffer)
	{
		perror("#cisfun$: memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	*line = buffer;
	while (1 & (stream == stdin))
	{
		fflush(stdout);
		character = _getchar();

		if (character == EOF || character == '\n')
		{
			buffer[chars] = '\0';
			break;
		}

		else
		{
			buffer[chars] = character;
			chars++;
		}

		if (chars >= *line_size)
		{
			*line_size += 32;
			buffer = _realloc(buffer, *line_size, *line_size * sizeof(char));
			if (!buffer)
			{
				perror("#cisfun$: memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
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
	void *tmp;
	unsigned int i, j;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		tmp = malloc(new_size);
		if (tmp == NULL)
			return (NULL);
		return (tmp);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	tmp = malloc(new_size);
	if (tmp == NULL)
		return (NULL);
	for (i = 0; i < old_size && i < new_size; i++)
			tmp[i] = ((char *)ptr)[i];
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

