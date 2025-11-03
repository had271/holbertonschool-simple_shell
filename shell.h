#ifndef SHELL_H
#define SHELL_H
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
int main (void);
int BettBett (void);
extern char **environ;
#endif
