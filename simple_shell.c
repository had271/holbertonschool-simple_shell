#include "shell.h"
/**
	* main - UNIX command line interpreter
	* Return: always 0
	*/
int main(void)
{
shell_loop();
return (EXIT_SUCCESS);
}
/**
	* shell_loop - loop function
	*/
void shell_loop(void)
{
char *line;
	int status;

	do {
	if (isatty(STDIN_FILENO))
	printf("#cisfun$ ");
	line = shell_read_line();
	if (line[0] == '\n' || strspn(line, " \t\r\n") == strlen(line))
	{
	free(line);
	continue;
	}
	line[strcspn(line, "\n")] = '\0';
	line[strcspn(line, "\t")] = '\0';
	status = shell_execute(line);

	free(line);
	} while (status);
}
/**
	* shell_read_line - read function
	* Return: line
	*/
char *shell_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
	exit(EXIT_SUCCESS);
	}
	else
	{
	perror("readline");
	exit(EXIT_FAILURE);
	}
	}

	return (line);
}
/**
	* shell_execute - execute function
	* @line: argument
	* Return: 1
	*/
int shell_execute(char *line)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *argv[2];

		argv[0] = line;
		argv[1] = NULL;
		execve(line, argv, environ);
		perror(line);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
	perror("fork");
	}
	else
	{
	wait(NULL);
	}

	return (-1);
}
