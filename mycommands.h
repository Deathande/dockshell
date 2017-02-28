#ifndef __MY_COMMANDS
#define __MY_COMMANDS

#include <stdio.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int cat   (int num_args, char** args);
int ls    (int num_args, char** args);
int clear (int num_args, char** args);
int cp    (int num_args, char** args);
int grep  (int num_args, char** args);

#endif
