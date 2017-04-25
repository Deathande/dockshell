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
  if (strcmp(toks[0], "cat") == 0)
  {
    cat(size, toks);
  }
  else if (strcmp(toks[0], "ls") == 0)
  {
    ls(size, toks);
  }
  else if (strcmp(toks[0], "cp") == 0)
  {
    cp(size, toks);
  }
  else if (strcmp(toks[0], "grep") == 0)
  {
    grep(size, toks);
  }
  else if (strcmp(toks[0], "clear") == 0)
  {
    clear(size, toks);
  }
  else if (strcmp(toks[0], "exit") == 0)
  {
    printf("exit\n");
    exit(0);
  }
  else if (strcmp(toks[0], "cd") == 0)
  {
    cd(size, toks);
  }
  else if (strcmp(toks[0], "mkdir") == 0)
  {
    mkdir_builtin(size, toks);
  }
  else if (strcmp(toks[0], "rmdir") == 0)
  {
    rmdir_builtin(size, toks);
  }
  else if (strcmp(toks[0], "stat") == 0)
  {
    stat_builtin(size, toks);
  }
  else if (strcmp(toks[0], "sleep") == 0)
  {
    sleep_builtin(size, toks);
  }
  else if (strcmp(toks[0], "env") == 0)
  {
     env(size, toks);
  }
  else if (strcmp(toks[0], "kill") == 0)
  {
    kill_builtin(size, toks);
  }
  else if (strcmp(toks[0], "timeout") == 0)
  {
    timeout(size, toks);
  }
  else if (strcmp(toks[0], "diff") == 0)
  {
    diff(size, toks);
  }
  else
  {
    printf("Unknwon command\n");
  }
}
