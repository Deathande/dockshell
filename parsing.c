#include "parsing.h"

void tokenize(char* str, char*** tokens, unsigned int* size)
{
  int i = 0;
  *tokens = malloc(sizeof(char*) * 40);
  *size = 0;
  while (i < strlen(str))
  {
    i = skip_whitespace(str, i);
    (*tokens)[*size] = malloc(sizeof(char) * 100);
    int ii = 0;
    if (str[i] == '\"')
    {
      i++; // ignore the first '"'
      while (i+ii < strlen(str) && str[i+ii] != '\"')
      {
        (*tokens)[*size][ii] = str[i+ii];
        ii++;
      }
      i++; // ignore the last '"'
    }
    else
    {
      while (i+ii < strlen(str) && str[i+ii] != ' ')
      {
        (*tokens)[*size][ii] = str[i+ii];
        ii++;
      }
    }
    (*tokens)[*size][ii] = '\000';
    i += ii;
    *size += 1;
  }
}

int skip_whitespace(char* str, int pos)
{
  while ((pos < strlen(str) && (str[pos] == ' ')))
  {
    pos++;
  }
  return pos;
}

void parse(char** toks, unsigned int size)
{
 /* 
  * Indicies of strings and corresponding function 
  * must line up.
  */
  char* commands[16] = {
    "cat", "ls", "cp", "grep", "clear", 
    "cd", "mkdir", "rmdir", "stat", "sleep", 
    "env", "kill", "timeout", "diff", "wait",
    "fork_test"
  };
  /* Array of function pointers */
  int (*function[16])(int, char**) = {
    &cat, &ls, &cp, &grep, &clear,
    &cd, &mkdir_builtin, &rmdir_builtin, &stat_builtin, &sleep_builtin,
    &env, &kill_builtin, &timeout, &diff, &wait_builtin, &fork_test
  };

  /* Exit does not follow the same argument pattern */
  if (strcmp(toks[0], "exit") == 0)
    exit(0);

 /* Linear search for the appropriate built in command */
  for (int i = 0; i < 16; i++)
  {
    if (strcmp(toks[0], commands[i]) == 0)
    {
      function[i](size, toks);
      return;
    }
  }
  printf("Unknown command\n");
}
