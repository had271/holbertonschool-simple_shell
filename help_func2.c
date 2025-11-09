#include "main.h"

/**
 * _getline - custom getline implementation
 * @lineptr: pointer to buffer pointer
 * @n: pointer to buffer size
 * Return: number of chars read, or -1 on EOF/error
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[1024];
	static int buf_pos, buf_len;
	int i = 0;
	char c;

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 1024;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (buf_pos >= buf_len)
		{
			buf_len = read(STDIN_FILENO, buffer, 1024);
			buf_pos = 0;

			if (buf_len <= 0)
				return (i > 0 ? i : -1);
		}

		c = buffer[buf_pos++];

		if (i >= (int)(*n - 1))
		{
			unsigned int old_size = *n;
			
			*n = *n * 2;
			*lineptr =_realloc(*lineptr, old_size, *n);
			if (*lineptr == NULL)
				return (-1);
		}

		(*lineptr)[i++] = c;

		if (c == '\n')
		{
			(*lineptr)[i] = '\0';
			return (i);
		}
	}
}
