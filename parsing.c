#include "parsing.h"

void tokenize(char* str, char*** tokens, unsigned int* size)
{
  char* token;
  int i = 0;

  *tokens = malloc(sizeof(char*));

  token = strtok(str, " ");
  (*tokens)[i] = token;
  i++;
  while (token != NULL)
  {
    *tokens = realloc(*tokens, (i+1) * sizeof(char*));
    token = strtok(NULL, " ");
    (*tokens)[i] = token;
    i++;
  }

  *size = i-1;
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
  else
  {
    printf("Unknwon command\n");
  }
}
