#include "main.h"

/**
 * myshell_cd - function to change directory
 * @args: pointer
 * Return: 1 or exit
*/

int myshell_cd(char **args)
{
	if (args == NULL)
	write(STDOUT_FILENO, "Please enter a command\n", 23);
	else if (chdir(args[1]) != 0)
	{
		perror("hsh");
		exit(EXIT_FAILURE);
	}
return (1);
}

/**
 * myshell_env - function that prints the current environment
 * @args: pointer
 * Return: 1
*/

int myshell_env(__attribute__((unused)) char **args)
{
	char **envir;

	for (envp = environ; *envir; envir++)
	{
		write(STDOUT_FILENO, *envir, _strlen(*envir));
		write(STDOUT_FILENO, "\n", 1);
	}
return (1);
}

/**
 * myshell_help - function to perfom help from shell
 * @args: pointer
 * Return: 0
*/

int myshell_help(__attribute__((unused)) char **args)
{
	write(STDOUT_FILENO, "Help list \n", 13);
	write(STDOUT_FILENO, "cd - change the current directory\n", 36);
	write(STDOUT_FILENO, " example: cd .., cd [directorypath]\n", 35);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "  exit - cause normal process termination\n", 42);
	write(STDOUT_FILENO, "  example: exit\n", 16);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "  help - display useful information\n", 36);
	write(STDOUT_FILENO, "  example: help\n", 16);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "  Also support commands like\n", 29);
	write(STDOUT_FILENO, "  cp - copy files and directories\n", 35);
	write(STDOUT_FILENO, " clear - clear the terminal screen\n", 36);
	write(STDOUT_FILENO, " cat - print on the standard output\n", 37);
	write(STDOUT_FILENO, " echo - display a line of text\n", 31);
	write(STDOUT_FILENO, "  mkdir - create a new folder\n", 30);
return (1);
}

/**
 * myshell_exit - function to exit from shell
 * @args: pointer to an array of pointers holding the arguments
 * Return: 0, always success
*/

int myshell_exit(__attribute__((unused)) char **args)
{
	return (2);
	/*return (0);*/
}
