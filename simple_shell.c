#include "main.h"

/**
	* main - open shell, project base
	* Return: int
	*/

int main(void)
{
	char *buff = NULL, **args, *orig0;
	size_t read_size = 0;
	ssize_t buff_size = 0;
	int exit_status = 0;

	while (1)
	{
		if (isatty(0))
			printf("hsh$ ");

		buff_size = _getline(&buff, &read_size);
		if (buff_size == -1 || _strcmp("exit\n", buff) == 0)
		{
			break;
		}

		buff[buff_size - 1] = '\0';

		if (_strcmp("env", buff) == 0)
		{
		_env();
		continue;
		}

		if (empty_line(buff) == 1)
		{
		exit_status = 0;
		continue;
		}
		if (_strncmp(buff, "setenv", 6) == 0)
		{
    		args = _split(buff, " ");
    		if (args[1] && args[2])
        		_setenv(args[1], args[2]);
				_env();
    		else
				write(2, "Usage: setenv VARIABLE VALUE\n", 29);
			free(args);
			continue;
		}
		if (_strncmp(buff, "unsetenv", 8) == 0)
		{
			args = _split(buff, " ");
    		if (args[1])
        		_unsetenv(args[1]);
				_env();
    		else
				write(2, "Usage: unsetenv VARIABLE\n", 25);
			free(args);
			continue;
		}
		args = _split(buff, " ");
		orig0 = args[0];
		args[0] = search_path(args[0]);
		if (args[0] == NULL)
		{
		perror("./hsh");
		free(args);
		continue;
		}

		exit_status = execute(args);
		if (args[0] != orig0)
			free(args[0]);
		free(args);
		}
	free(buff);
	return (exit_status);
}

char *search_path(char *command)
{
	char *path = _getenv("PATH"), *path_cpy;
	char **path_split;
	char *path_concat = NULL;
	int i = 0, path_len = 0;
	struct stat info;

	if (stat(command, &info) == 0)
	return (command);

	if (!path)
	return (NULL);

	path_cpy = malloc(_strlen(path) + 1);
	if (!path_cpy)
	return (NULL);

	_strcpy(path_cpy, path);
	path_split = _split(path_cpy, ":");
	if (!path_split)
	{
	free(path_cpy);
	return (NULL);
	}

	while (path_split[i])
	{
	path_len = _strlen(path_split[i]);
	path_concat = malloc(path_len + _strlen(command) + 2);
	if (!path_concat)
	{
	i++;
	continue;
	}

	_strcpy(path_concat, path_split[i]);
	_strcat(path_concat, "/");
	_strcat(path_concat, command);

	if (stat(path_concat, &info) == 0)
	break;

	free(path_concat);
	path_concat = NULL;
	i++;
	}

	free(path_cpy);
	free(path_split);

	return (path_concat);
}

/**
	* execute - execute command path, child process
	* @args: arguments
	* Return: exit status
	*/

int execute(char **args)
{
	int id = fork(), status;

	if (id == 0)
	{
	if (execve(args[0], args, environ) == -1)
	perror("Error");
	}
	else
	{
	wait(&status);
	if (WIFEXITED(status))
	status = WEXITSTATUS(status);
	}

	return (status);
}

/**
	* _getenv - get env variables
	* @env_var: env variable
	* Return: env variable result, its content
	*/
char *_getenv(char *env_var)
{
    int i = 0;
    size_t len;
    size_t j;
    int match;

    if (env_var == NULL)
        return (NULL);

    len = _strlen(env_var);

    while (environ[i])
    {
        match = 1;
        for (j = 0; j < len; j++)
        {
            if (environ[i][j] != env_var[j])
            {
                match = 0;
                break;
            }
        }

        if (match == 1 && environ[i][len] == '=')
            return (&environ[i][len + 1]);

        i++;
    }
    return (NULL);
}

/**
	* _env - prints environment
*/
void _env(void)
{
	int i = 0;

	while (environ[i])
	{
	printf("%s\n", environ[i]);
	i++;
	}
}
