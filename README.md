# Simple Shell

## Overview
The **Simple Shell** project is a basic UNIX command interpreter written in C.  
It provides a minimal version of the standard shell (`/bin/sh`) that can execute commands,
handle arguments, manage the PATH, and support built-in commands like `exit` and `env`.

## Compilation
Compile all source files using:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage
**Interactive mode**
``` $ ./hsh
($) /bin/ls
main.c shell.c test_folder
($) exit
$
```

**Non-interactive mode**
```$ echo "/bin/ls" | ./hsh
main.c shell.c test_folder
$
```

## Features
- Display a prompt and wait for user input
- Execute commands with arguments
- Handle the PATH
- Support built-in commands (`exit`, `env`)
- Manage errors similar to `/bin/sh`
- Work in both interactive and non-interactive modes

## Project Stages
9. Simple shell 0.1.1

Handle command lines with arguments.
**Example:**
```bash
($) /bin/ls -l /tmp
total 0
-rw------- 1 user user 0 Jan 20 14:33 file1
-rw------- 1 user user 0 Jan 20 14:33 file2
($)
```

## 10. Simple shell 0.2.1

Handle the PATH.
fork must not be called if the command doesn’t exist.
**Example:**
```
($) ls /var
log tmp
($) ls nonexistent
./hsh: No such file or directory
($)
```
# 11. Simple shell 0.4.1

Implement the exit built-in command.
**Usage:**
```
($) exit
$
```

# 19. Comments

Handle comments (#) in the input.
Everything after # on a line is ignored.
**Example:**
```
($) ls # this is a comment
main.c shell.c
($)
```

# 22. File as input

Allow the shell to execute commands from a file.
**Example:**
```
$ cat testfile
/bin/ls
/bin/pwd
$ ./hsh testfile
main.c shell.c
/home/user/simple_shell
$
```

