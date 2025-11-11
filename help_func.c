#include "main.h"

/**
	* execute_command - executes an external command
	* @args: tokenized command
	* @envp: environment variables
	*
	* Return: exit status of the command
	*/
int execute_command(char *args[], char **envp)
{
	pid_t pid;
	int status;
	char *path_cmd;

	path_cmd = find_command(args[0], envp);
	if (!path_cmd)
	{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, args[0], strlen(args[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	return (127);
	}

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	free(path_cmd);
	return (1);
	}
	else if (pid == 0)
	{
	execve(path_cmd, args, envp);
	perror("execve");
	_exit(EXIT_FAILURE);
	}
	else
	{
	wait(&status);
	free(path_cmd);
	if (WIFEXITED(status))
	return (WEXITSTATUS(status));
	return (1);
	}
}

/**
	* try_cmd_path - checks if cmd exists in a given directory
	* @dir: directory path
	* @cmd: command name
	*
	* Return: full path string (malloced) if executable, NULL otherwise
	*/
char *try_cmd_path(char *dir, char *cmd)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);

	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
	* cmd_with_slash - checks if cmd contains '/' and is executable
	* @cmd: command
	*
	* Return: malloced path if executable, NULL otherwise
	*/
char *cmd_with_slash(char *cmd)
{
	char *full_path;

	if (!cmd || !strchr(cmd, '/'))
		return (NULL);

	if (access(cmd, X_OK) != 0)
		return (NULL);

	full_path = malloc(strlen(cmd) + 1);
	if (!full_path)
		return (NULL);

	strcpy(full_path, cmd);
	return (full_path);
}

/**
	* find_command - finds the full path of a command
	* @cmd: the command to find
	* @envp: environment variables
	*
	* Return: full path string (malloced) or NULL if not found
	*/
char *find_command(char *cmd, char **envp)
{
	char *path_env, *path_dup, *dir, *full_path;

	if (!cmd)
		return (NULL);

	full_path = cmd_with_slash(cmd);
	if (full_path)
		return (full_path);

	path_env = get_path_env(envp);
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_dup = malloc(strlen(path_env) + 1);
	if (!path_dup)
		return (NULL);
	strcpy(path_dup, path_env);

	dir = strtok(path_dup, ":");
	while (dir)
	{
		full_path = try_cmd_path(dir, cmd);
		if (full_path)
		{
			free(path_dup);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}

/**
	* trim - removes leading and trailing spaces and tabs from a string
	* @str: the string to trim
	*
	* Return: pointer to the trimmed string, or NULL if str is NULL
	*/
char *trim(char *str)
{
	char *end;

	if (!str)
		return (NULL);

	while (*str == ' ' || *str == '\t')
	str++;

	if (*str == 0)
	return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
	*end-- = '\0';

	return (str);
}
