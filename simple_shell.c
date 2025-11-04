#include "shell.h"
/**
 * main - UNIX command line interpreter
 * Return: always 0
 */
int main(void)
{
shell_loop();
return EXIT_SUCCESS;
}
/**
 * shell_loop - loop function
 * Return: always 0
 */
int shell_loop(void)
{
char *line;
  char **args;
  int status;

  do {
    printf("#cisfun$ ");
    line = shell_read_line();
        if (line[0] == '\n') {
      free(line);
      continue;
    }
    line[strcspn(line, "\n")] = '\0';
    status = shell_execute(args);

    free(line);
  } while (status);
  return (0);
}
/**
 * shell_read_line - read function
 * Return: line
 */
char *shell_read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return (line);
}
/**
 * shell_execute - execute function
 * Return: 1
 */
int shell_execute(char *line)
{
  pid_t pid = fork();

  if (pid == 0) {
    char *argv[] = {line, NULL};

    execve(line, argv, environ);
    perror(line);
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("fork");
  } else {
    wait(NULL);
  }

  return (1);
}
