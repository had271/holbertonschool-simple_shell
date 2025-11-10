#include "main.h"

/**
 * myshell_execute - function to run external or built in
 * @args: pointer to an array
 * Return: int
*/

int myshell_execute(char **args)
{
	int i = 0, counter = 0;
	char *builtin_name[] = {"cd", "exit", "env", "help"};

	int (*builtin_func[]) (char **) = {&myshell_cd, &myshell_exit, &myshell_env, &myshell_help};
	if (args == NULL)
	return (1);
	counter = sizeof(builtin_name) / sizeof(char *);
	while (i < counter)
	{
		if (_strcmp(args[0], builtin_name[i]) == 0)
		return (builtin_func[i](args));
		i++;
	}

return (myshell_external(args));
}

/**
 * myshell_external - function to run an external proccess
 * @args: pointer to an array of pointers holding the arguments
 * Return: 1 on success, otherwise just give exit values
 * depending on error
*/

int myshell_external(char **args)
{
	char *path = NULL, *env_PATH, **directories = NULL, *directories_cpy;
	int i, j;

	env_PATH = _getenv("PATH");
	directories = split_path(env_PATH);
	free(env_PATH);
	for (j = 0; directories[j]; j++)
	{
		if (_strncmp(args[0], directories[j], _strlen(directories[j])) == 0)
		{
			path = args[0];
			if (access(path, X_OK) != 0)
			return (no_exec_found(directories));
			_execve(path, args);
			return (wait_free_directories(directories));
		}
	}
	for (i = 0; directories[i]; i++)
	{
		directories_cpy = malloc(1024 * sizeof(char));
		if (directories_cpy == NULL)
		{
			perror("hsh: failed to allocate directories_cpy\n");
			break;
		} _strcpy(directories_cpy, directories[i]);
		_strcat(directories_cpy, args[0]);
		path = directories_cpy;
		if (access(path, X_OK) != 0)
		free(directories_cpy);
		else
		break;
	}
if (!directories[i])
{
	if (execve(args[0], args, environ) == -1)
	return (no_exec_found(directories));
	return (1);
} _execve(path, args);
free(path);
return (wait_free_directories(directories));
}

/**
 * wait_free_directories - function to wait and free a double pointer
 * @directories: double pointer
 * Return: 1, always success
*/

int wait_free_directories(char **directories)
{
	int wait_status, i;

	wait(&wait_status);

	for (i = 0; directories[i]; i++)
	{
		free(directories[i]);
	}

	free(directories);

return (1);
}

/**
 * no_exec_found - function to happen when executable is not found
 * @directories: double pointer holding array of strings (directories paths)
 * Return: nothing, always success
*/

int no_exec_found(char **directories)
{
	perror("cisfun");
	free_double_pointer(directories);
	return (1);
}

/**
 * _execve - function to run execv with the path
 * @path: pointer for path
 * @args: pointer for the arguments
 * Return: 1 or 0
*/

int _execve(char *path, char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror("cisfun");
			return (0);
		}
	}
	else if (pid < 0)
	{
		perror("cisfun");
		return (0);
	}

return (1);
}

