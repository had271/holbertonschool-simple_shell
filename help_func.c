#include "main.h"

/**
 * _getenv - function to get an enviroment variable
 * @name: pointer
 * Return: pointer
*/

char *_getenv(const char *name)
{
	char **envir;
	char *buffer;
	size_t buf_size = 1024, path_len;

	if (name == NULL)
	{
		perror("#cisfun$: enter a valid env\n");
		exit(EXIT_FAILURE);
	}

	envir = environ;
	buffer = malloc(sizeof(char) * buf_size);
	if (!buffer)
	{
		perror("#cisfun$:");
		exit(EXIT_FAILURE);
	}

	while (*envir)
	{
		if (_strncmp(*envir, name, _strlen(name)) == 0)
		{
			path_len = _strlen(*envir);

			if (path_len >= buf_size)
			{
				buffer = realloc(buffer, buf_size);
				if (!buffer)
				{
					free(buffer);
					perror("#cisfun$: failed allocating memory");
					exit(EXIT_FAILURE);
				}
			}
			_strcpy(buffer, *envir);
			break;
		}
		envir++;
	}
return (buffer);
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
		for (j = 0; j < new_size; j++)
		{
			((char *)tmp)[j] = ((char *)ptr)[j];
		}
		free(ptr);
		return (tmp);
	}
	return (NULL);
}

/**
 * free_double_pointer - function to free a pointer
 * @directories: pointer
*/

void free_double_pointer(char **dirs)
{
	int i;

	for (i = 0; dirs[i]; i++)
	{
		free(dirs[i]);
	}
	free(dirs);
}
