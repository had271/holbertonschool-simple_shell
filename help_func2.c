#include "main.h"

/**
	* get_path_env - retrieves the value of the PATH environment variable
	* @envp: array of environment variables
	*
	* Return: pointer to the PATH string (skipping "PATH=") if found,
	*         NULL otherwise
	*/
char *get_path_env(char **envp)
{
	int i = 0;

	if (!envp)
	return (NULL);

	while (envp[i])
	{
	if (strncmp(envp[i], "PATH=", 5) == 0)
	return (envp[i] + 5);
	i++;
	}
	return (NULL);
}

/**
	* handle_builtins - executes built-in commands if found
	* @args: tokenized command
	* @line: input line to free if exit
	* @envp: environment variables
	* @status: pointer to shell status
	*
	* Return: 1 if a built-in was executed, 0 otherwise
	*/
int handle_builtins(char *args[], char *line, char **envp, int *status)
{
	int i;

	if (!args[0])
	return (1);

	if (strcmp(args[0], "exit") == 0)
	{
	free(line);
	exit(*status);
	}

	if (strcmp(args[0], "env") == 0)
	{
	for (i = 0; envp[i]; i++)
	{
	write(STDOUT_FILENO, envp[i], strlen(envp[i]));
	write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
	}
	return (0);
}

/**
	* handle_env - prints the current environment if command is "env"
	* @args: array of command arguments
	* @envp: array of environment variables
	*
	* Return: 1 if the command was "env", 0 otherwise
	*/
int handle_env(char *args[], char **envp)
{
	int j;

	if (strcmp(args[0], "env") == 0)
	{
	for (j = 0; envp[j]; j++)
	{
	write(STDOUT_FILENO, envp[j], strlen(envp[j]));
	write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
	}
	return (0);
}

/**
	* handle_exit - exits the shell if command is "exit"
	* @args: array of command arguments
	* @line: input line to free
	* @status: current exit status
	*
	* Return: status (exits the program if "exit" is called)
	*/

int handle_exit(char **args, int last_status) 
{
    int status;
    
    if (args[1] == NULL) {
        exit(last_status);
    }
    
    char *endptr;
    long num = strtol(args[1], &endptr, 10);
    
    if (*endptr != '\0' || args[1][0] == '\0') {
        fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
        return (2); 
    }
    
    status = ((num % 256) + 256) % 256;
    exit(status);
}


/**
 * is_executable - checks if a file is executable
 * @path: path to the file
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}

