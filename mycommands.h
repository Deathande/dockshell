#ifndef __MY_COMMANDS
#define __MY_COMMANDS

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "parsing.h"
#include "helpers.h"

#ifdef HAVE_ST_BIRTHTIME
#define birthtime(x) x->st_birthtime
#else
#define birthtime(x) x->st_ctime
#endif

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
int wait_builtin    (int num_args, char** args);
int sleep_builtin   (int num_args, char** args);
int kill_builtin    (int num_args, char** args);

/* Extra function to test wait with. */
/* Wait will only wait for child processes, so */
/* This command starts a child process that sleeps */
/* for 10 then exits. The pid of the child process is */
/* printed and can be given as the first argument to wait. */
int fork_test       (int, char**);

#endif
