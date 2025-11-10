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
	if (signal == SIGINT)
	write(1, "\n($)", 4);
}

/**
 * myshell_loop - function that will mantain my shell running
*/
void myshell_loop(void)
{
	char *usercommand, **args;
	int shell_status;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
	perror("cisfun");
	if (isatty(STDIN_FILENO) != 1)
	{
		while (1)
		{
			usercommand = read_command();
			args = split_into_arguments(usercommand);
			myshell_execute(args);
			free(args);
			free(usercommand);
		}
		return;
	}
	else
	{
		do {
		printf("($)");
		user_command = read_command();
		while (*user_command == '\0') 
		{
			free(user_command);
			printf("($)");
			user_command = read_command();
		}
		args = split_into_arguments(user_command);
		if (args == NULL)
		break;
		shell_status = myshell_execute(args);
		free(user_command);
		free(args);
		if (shell_status == 2)
		exit(EXIT_SUCCESS);
		} while (shell_status);
	}
}

/**
 * split_into_arguments - function to splite the line
 * @line: Pointer
 * Return: Pointer
*/
char **split_into_arguments(char *line)
{
	int i, commands_size = 32;
	char **commands, *toke = NULL;

	commands = malloc(commands_size * sizeof(char *));
	if (commands == NULL)
	{
		perror("#cisfun$ failed to allocate memory\n");
		return (NULL);
	}
	tok = strtok(line, " \t\n\r\a");
	if (toke == NULL)
	{
		free(commands);
		return (NULL);
	}
	else
	{
		i = 0;
		while (toke != NULL)
		{
			commands[i] = toke;
			toke = strtok(NULL, " \n");
			i++;

			if (i >= commands_size)
			{
				commands_size += 1024;
				commands = _realloc(commands, commands_size,
										commands_size * sizeof(char *));
				if (commands == NULL)
				{
					perror("#cisfun$ failed to realloc commands\n");
					return (NULL);
				}
			}
		}
		commands[i] = NULL;
	}
return (commands);
}


/**
 * split_path - function to split env variable PATH into tokens
 * @path: pointer
 * Return: Pointer
*/
char **split_path(char *path)
{
	unsigned int i;
	char *toke = NULL, **dir;
	size_t dir_size = 32;

	dir = malloc(sizeof(char *) * dir_size);
	if (dir == NULL)
	{
		perror("split_path: failed to allocate dir\n");
		exit(EXIT_FAILURE);
	} toke = strtok(path, "= :");
	toke = strtok(NULL, "= :");
	if (toke == NULL)
	{
		free(dir);
		perror(" enter a path\n");
		exit(EXIT_FAILURE);
	} else
	{
		i = 0;
		while (toke != NULL)
		{
			dir[i] = malloc(sizeof(char) * (_strlen(toke) + 2));
			if (dir[i] == NULL)
			{
				free(dir);
				perror("#cisfun$ failed to allocate dir[i]\n");
				exit(EXIT_FAILURE);
			} _strcpy(dir[i], toke);
			_strcat(dir[i], "/");
			toke = strtok(NULL, "= :");
			i++;
			if (i >= dir_size)
			{
				dir_size += 32;
				dir = _realloc(dir, dir_size, dir_size * sizeof(char *));
				if (dir == NULL)
				perror("#cisfun$ failed to reallocate dir\n");
			}
		} dir[i] = NULL;
	} return (dir);
}
