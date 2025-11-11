#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
extern char **environ;
int BettBett(void);
int _isspace(char *s);
char *trim(char *str);
int is_executable(char *path);
char *get_path_env(char **envp);
char *find_command(char *cmd, char **envp);
char *try_cmd_path(char *dir, char *cmd);
char *cmd_with_slash(char *cmd);
int parse_command(char *line, char *args[]);
int handle_builtins(char *args[], char *line, char **envp, int *status);
int execute_command(char *args[], char **envp);
int handle_exit(char **args, int last_status);
#endif
