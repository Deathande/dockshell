#ifndef __MY_COMMANDS
#define __MY_COMMANDS

#include <stdio.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

/* Phase 1 */
int cat     (int num_args, char** args);
int ls      (int num_args, char** args);
int clear   (int num_args, char** args);
int cp      (int num_args, char** args);
int grep    (int num_args, char** args);

/* Phase 2 */
int cd      (int num_args, char** args);
int mkdir   (int num_args, char** args);
//int rmdir   (int num_args, char** args);
int stat    (int num_args, char** args);
//int sleep   (int num_args, char** args);
int kill    (int num_args, char** args);
int diff    (int num_args, char** args);
int env     (int num_args, char** args);
int timeout (int num_args, char** args);
int wait    (int num_args, char** args);

#endif
