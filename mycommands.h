#ifndef __MY_COMMANDS
#define __MY_COMMANDS

#include <stdio.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <unistd.h>

int cat(int num_args, char** args);
int ls(int num_args, char** args);
int clear(unsigned int num_args, char** args);

#endif
