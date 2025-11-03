#include "shell.h"
/**
 * main - UNIX command line interpreter
 * Return: always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf("#cisfun$ ");
	if (getline(&line, &len, stdin) == -1)
	break;

	if (line[0] == '\n')
	continue;
	line[strcspn(line, "\n")] = '\0';
	pid = fork();
	if (pid == 0)
	{
	char *argv[2];

	argv[0] = line;
	argv[1] = NULL;
	execve(line, argv, environ);
	perror(line);
	exit(1);
	}
	else
	wait(NULL);
	}
	free(line);
	return (0);
}
