#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sysy/tpes.h>
#include <limit.h>
#include <errno.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define CONVERT_LOWERCASE
#define CONVERT_UNSIGNED

#define USE_GETLINE 0
#define USE_STRTOK 0

#define MAX_COMMAND_LENGTH 50


#endif
