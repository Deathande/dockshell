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
      i++; // ignore the '"'
      while (i+ii < strlen(str) && str[i+ii] != '\"')
      {
        (*tokens)[*size][ii] = str[i+ii];
        ii++;
      }
    }
    else
    {
      while (i+ii < strlen(str) && str[i+ii] != ' ')
      {
        (*tokens)[*size][ii] = str[i+ii];
        ii++;
      }
    }
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
  else
  {
    printf("Unknwon command\n");
  }
}
