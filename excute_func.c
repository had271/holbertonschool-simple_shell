#include "main.h"

/**
 * myshell_execute - function to run external or built in
 * @args: pointer to an array
 * Return: int
*/

int myshell_execute(char **args)
{
	int i = 0;
	int builtin_count = 4;
	char *builtin_name[] = {"cd", "exit", "env", "help"};
	int (*builtin_func[]) (char **) = {&myshell_cd, &myshell_exit, &myshell_env, &myshell_help};

	if (!args || !args[0])
		return (1);
	for (i = 0; i < builtin_count; i++)
	{
		if (_strcmp(args[0], builtin_name[i]) == 0)
			return (builtin_func[i](args));
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
	char *env_PATH = NULL;
	char **directories = NULL;
	pid_t child_pid = -1;
	int found = 0;

	if (!args || !args[0])
		return (1);
	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
		{
			child_pid = _execve(args[0], args);
			return (wait_free_directories(child_pid, NULL));
		}
		else
		{
			return (no_exec_found(NULL));
		}
	}
	env_PATH = _getenv("PATH");
	if (!env_PATH)
	{
		return (no_exec_found(NULL));
	}
	directories = split_path(env_PATH);
	free(env_PATH);
	for (int i = 0; directories && directories[i]; i++)
	{
		size_t need = _strlen(directories[i]) + _strlen(args[0]) + 1;
		char *candidate = malloc(need);
		if (!candidate)
		{
			perror("malloc");
			no_exec_found(directories);
			return (1);
		}
		_strcpy(candidate, directories[i]);
		_strcat(candidate, args[0]);
		if (access(candidate, X_OK) == 0)
		{
			child_pid = _execve(candidate, args);
			free(candidate);
			found = 1;
			return (wait_free_directories(child_pid, directories));
		}
		free(candidate);
	}
	return (no_exec_found(directories));
}

/**
 * wait_free_directories - function to wait and free a double pointer
 * @directories: double pointer
 * Return: 1, always success
*/

int wait_free_directories(char **directories)
{
	int status, i;

	if (child_pid > 0)
		waitpid(child_pid, &status, 0);
	else
		wait(&status);
	if (directories)
	{
		for (i = 0; directories[i]; i++)
			free(directories[i]);
		free(directories);
	}
return (1);
}

/**
 * no_exec_found - function to happen when executable is not found
 * @directories: double pointer holding array of strings (directories paths)
 * Return: nothing, always success
*/

int no_exec_found(char **directories)
{
	write(STDERR_FILENO, "hsh: command not found\n", 23);
	if (directories)
	{
		for (int i = 0; directories[i]; i++)
			free(directories[i]);
		free(directories);
	}
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
	if (pid == -1)
	{
			perror("fork");
			return (-1);
	}
	if (pid == 0)
	{
		execve(path, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return ((int)pid);
}


