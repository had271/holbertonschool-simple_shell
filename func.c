#include "main.h"

/**
	* _isspace - checks if a string contains only whitespace characters
	* @str: the string to check
	*
	* Return: 1 if the string is NULL or only spaces/tabs/newlines,
	*         0 if any other character is found
	*/
int _isspace(char *str)
{
	int i = 0;

	if (!str)
	return (1);

	while (str[i])
	{
	if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	return (0);
	i++;
	}
	return (1);
}

/**
	* main - entry point for simple shell
	* @argc: argument count
	* @argv: argument vector
	* @envp: environment variables
	*
	* Return: last command exit status
	*/
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *command;
	char *args[100];
	int status = 0;

	(void)argc;
	(void)argv;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, ":) ", 3);

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "\n", 1);
	break;
	}

	command = trim(line);
	if (!_isspace(command))
	{
	parse_command(command, args);
	if (handle_builtins(args, line, envp, &status))
	continue;
	status = execute_command(args, envp);
	}
	}

	free(line);
	return (status);
}
