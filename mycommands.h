#ifndef __MY_COMMANDS
#define __MY_COMMANDS

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "parsing.h"

/* Phase 1 */
int cat     (int num_args, char** args);
int ls      (int num_args, char** args);
int clear   (int num_args, char** args);
int cp      (int num_args, char** args);
int grep    (int num_args, char** args);

/* Phase 2 */
int cd            (int num_args, char** args);
int mkdir_builtin (int num_args, char** args);
int rmdir_builtin (int num_args, char** args);
int stat_builtin  (int num_args, char** args);
int diff          (int num_args, char** args);
int env           (int num_args, char** args);
int timeout       (int num_args, char** args);
//int wait    (int num_args, char** args);
int sleep_builtin   (int num_args, char** args);
int kill_builtin    (int num_args, char** args);

#endif
