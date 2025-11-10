#ifndef MAIN_H
#define MAIN_H
#define _GNU_SOURCE
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
int main(void);
int _getchar(void);
ssize_t _getline(char **linep, ssize_t *line_size, FILE *stream);
void sig_handler(int signal);
char *read_command(void);
char **split_into_arguments(char *line);
void myshell_loop(void);
int myshell_execute(char **args);
int myshell_external(char **args);
int myshell_cd(char **args);
int myshell_exit(char **args);
int myshell_env(char **args);
int myshell_help(char **args);
char *_getenv(const char *name);
char **split_path(char *path);
int _execve(char *path, char **args);
void free_double_pointer(char **dirs);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
unsigned int _getpid(void);
int no_exec_found(char **directories);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
size_t _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int wait_free_directories(char **directories);
#endif
