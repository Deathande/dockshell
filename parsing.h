#ifndef _DOCKSHELL_PARSING
#define _DOCKSHELL_PARSING

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mycommands.h"

void tokenize(char*, char***, unsigned int*);
char** parse_args(char**, int);
char* get_string(char**, int, int);
void parse(char**, unsigned int);

#endif
