#include "main.h"
/**
 * _strncmp - compare n characters of 2 strings
 * @s1: first string
 * @s2: second string
 * @n: number of chars to compare
 * Return: difference or 0 if equal
*/
int _strncmp(char *s1, char *s2, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    }
    return (0);
}

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

/**
 * _setenv - initialize or modify environment variable
 * @var: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *var, char *value)
{
	int i = 0, len;
	char *new_env;
	
	if (!var || !value)
	{
		write(2, "setenv: invalid arguments\n", 26);
		return (-1);
	}

	len = _strlen(var);

	while (environ[i])
	{
		if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			new_env = malloc(len + _strlen(value) + 2);
			if (!new_env)
				return (-1);

			_strcpy(new_env, var);
			_strcat(new_env, "=");
			_strcat(new_env, value);
			environ[i] = new_env;
			return (0);
		}
		i++;
	}

	environ = _realloc(environ, sizeof(char *) * i, sizeof(char *) * (i + 2));
	if (!environ)
		return (-1);

	new_env = malloc(len + _strlen(value) + 2);
	if (!new_env)
		return (-1);

	_strcpy(new_env, var);
	_strcat(new_env, "=");
	_strcat(new_env, value);

	environ[i] = new_env;
	environ[i + 1] = NULL;
	return (0);
}
/**
 * _unsetenv - remove an environment variable
 * @var: variable name to remove
 * Return: 0 always
 */
int _unsetenv(char *var)
{
	int i = 0, j, len;

	if (!var)
	{
		write(2, "unsetenv: invalid arguments\n", 28);
		return (-1);
	}

	len = _strlen(var);

	while (environ[i])
	{
		if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];

			return (0);
		}
		i++;
	}
	return (0);
}
