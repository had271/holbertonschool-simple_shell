#include "main.h"

/**
 * main - my own shell
 * Return: always 0, success
*/
int main(void)
{
	myshell_loop();
	return (0);
}

/**
 * sig_handler - Function to happen when SINGIN is detected by signal
 * @signal: integer
*/
void sig_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * myshell_loop - function that will mantain my shell running
*/
void myshell_loop(void)
{
	char *usercommand = NULL, **args = NULL;
	int shell_status = 1;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		perror("signal");
	if (!isatty(STDIN_FILENO))
	{
		while (1)
		{
			usercommand = read_command();
			if (!usercommand) break;
			args = split_into_arguments(usercommand);
			myshell_execute(args);
			free(args);
			free(usercommand);
		}
		return (0);
	}
	else
	{
		do {
			printf("($)");
			fflush(stdout);
			usercommand = read_command();
			if (!usercommand)
				break;
			while (usercommand[0] == '\0')
			{
				free(usercommand);
				printf("($)");
				fflush(stdout);
				usercommand = read_command();
				if (!usercommand) break;
			}
			if (!usercommand) break;
			args = split_into_arguments(usercommand);
			if (args == NULL)
			{
				free(usercommand);
				continue;
			}
			shell_status = myshell_execute(args);
			free(args);
			free(usercommand);
			if (shell_status == 2)
				exit(EXIT_SUCCESS);
		} while (shell_status);
	}
	return (0);
}

/**
 * split_into_arguments - function to splite the line
 * @line: Pointer
 * Return: Pointer
*/
char **split_into_arguments(char *line)
{
	int i, commands_size = 32;
	char **commands, *toke;
	int old_count;

	if (!line)
		return (NULL);
	commands = malloc(commands_size * sizeof(char *));
	if (!commands)
	{
		perror("malloc commands");
		return (NULL);
	}
	toke = strtok(line, " \t\n\r\a");
	if (!toke)
	{
		free(commands);
		return (NULL);
	}
	while (toke)
	{
		commands[i++] = toke;
		if (i >= commands_size)
		{
			old_count = command_size;
			commands_size += 1024;
			commands = _realloc(commands, old_count * sizeof(char *),
				commands_size * sizeof(char *));
			if (!commands)
			{
				perror("realloc commands");
				return (NULL);
			}
		}
		toke = strtok(NULL, " \t\n\r\a");
	}
	commands[i] = NULL;
	return (commands);
}


/**
 * split_path - function to split env variable PATH into tokens
 * @path: pointer
 * Return: Pointer
*/
char **split_path(char *path)
{
	char *toke;
	char **dirs;
	size_t dirs_count = 32;
	size_t i = 0;

	if (path_value == NULL)
		return (NULL);

	dirs = malloc(sizeof(char *) * dirs_count);
	if (!dirs)
	{
		perror("split_path: malloc");
		exit(EXIT_FAILURE);
	}

	toke = strtok(path_value, ":");
	while (toke != NULL)
	{
		size_t len = _strlen(toke);

		dirs[i] = malloc(len + 2);
		if (!dirs[i])
		{
			perror("split_path: malloc dir");
			for (size_t k = 0; k < i; k++) free(dirs[k]);
			free(dirs);
			exit(EXIT_FAILURE);
		}
		_strcpy(dirs[i], toke);
		if (dirs[i][len - 1] != '/')
			_strcat(dirs[i], "/");
		i++;
		if (i >= dirs_count)
		{
			dirs_count += 32;
			dirs = _realloc(dirs, (unsigned int)(dirs_count - 32) * sizeof(char *),
							(unsigned int)dirs_count * sizeof(char *));
			if (!dirs)
			{
				perror("split_path: realloc failed");
				exit(EXIT_FAILURE);
			}
		}
		toke = strtok(NULL, ":");
	}
	dirs[i] = NULL;
	return (dirs);
}
