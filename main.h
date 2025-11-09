#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
int main(void);
int BettBett(void);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *search_path(char *command);
char **_split(char *str, char *sep);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_getenv(char *env_var);
void _env(void);
int execute(char **args);
int empty_line(char *buff);
extern char **environ;
void *_calloc(unsigned int nmemb, unsigned int size);
ssize_t _getline(char **lineptr, size_t *n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
