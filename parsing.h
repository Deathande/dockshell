#ifndef _DOCKSHELL_PARSING
#define _DOCKSHELL_PARSING

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mycommands.h"

void tokenize(char*, char***, unsigned int*);
void parse(char**, unsigned int);
int skip_whitespace(char* str, int pos);

#endif
