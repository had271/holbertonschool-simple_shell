#include "main.h"

/**
	* main - open shell, project base
	* Return: int
	*/

int main(void)
{
	char *buff = NULL, **args;
	size_t read_size = 0;
	ssize_t buff_size = 0;
	int exit_status = 0;
	char *orig0 = args[0];
	int allocated = 0;

	while (1)
	{
	if (isatty(0))
	printf("hsh$ ");

	buff_size = getline(&buff, &read_size, stdin);
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

	args = _split(buff, " ");
	args[0] = search_path(args[0]);
	if (args[0] == NULL)
	{
	perror("./hsh");
	free(args);
	continue;
	}

	exit_status = execute(args);
	if (args[0] != orig0)
		allocated = 1;
	if (allocated)
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
	int i = 0, j;
	int status;

	while (environ[i])
	{
	status = 1;

	for (j = 0; environ[i][j] != '='; j++)
	{
	if (environ[i][j] != env_var[j])
	status = 0;
	}
	if (status == 1)
	break;
	i++;
	}
	return (&environ[i][j + 1]);
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
