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

	while (1)
	{
	if (isatty(0))
	printf("hsh$ ");

	buff_size = getline(&buff, &read_size, stdin);
	if (buff_size == -1 || _strcmp("exit\n", buff) == 0)
	{
	free(buff);
	return (exit_status);
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
	free(args);
	}
	return (exit_status);
}

/**
	* split_path - function to split env variable PATH into tokens
	* @path: pointer holding PATH
	* Return: Pointer to an array of strings holding the tokens
*/
char **split_path(char *path)
{
	unsigned int i;
	char *tok = NULL, **dir;
	size_t dir_size = 32;

	dir = malloc(sizeof(char *) * dir_size);
	if (dir == NULL)
	{
	perror("split_path: failed to allocate dir\n");
	exit(EXIT_FAILURE);
	} tok = strtok(path, "= :");
	tok = strtok(NULL, "= :");
	if (tok == NULL)
	{
	free(dir);
	perror("Please enter a path\n");
	exit(EXIT_FAILURE);
	} else
	{
	i = 0;
	while (tok != NULL)
	{
	dir[i] = malloc(sizeof(char) * (_strlen(tok) + 2));
	if (dir[i] == NULL)
	{
	free(dir);
	perror("hsh: failed to allocate dir[i]\n");
	exit(EXIT_FAILURE);
	} _strcpy(dir[i], tok);
	_strcat(dir[i], "/");
	tok = strtok(NULL, "= :");
	i++;
	if (i >= dir_size)
	{
	dir_size += 32;
	dir = _realloc(dir, dir_size, dir_size * sizeof(char *));
	if (dir == NULL)
	perror("hsh: failed to reallocate dir\n");
	}
	} dir[i] = NULL;
	} return (dir);
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
