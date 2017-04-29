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
  char* commands[15] = {
    "cat", "ls", "cp", "grep", "clear", 
    "cd", "mkdir", "rmdir", "stat", "sleep", 
    "env", "kill", "timeout", "diff", "wait"
  };
  int (*function[15])(int, char**) = {
    &cat, &ls, &cp, &grep, &clear,
    &cd, &mkdir_builtin, &rmdir_builtin, &stat_builtin, &sleep_builtin,
    &env, &kill_builtin, &timeout, &diff, &wait_builtin
  };

  if (strcmp(toks[0], "exit") == 0)
  {
    printf("exit\n");
    exit(0);
  }

  for (int i = 0; i < 16; i++)
  {
    if (strcmp(toks[0], commands[i]) == 0)
    {
      function[i](size, toks);
      return;
    }
  }
  printf("Unknown command");
}
