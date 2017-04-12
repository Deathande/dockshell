#include "parsing.h"

void tokenize(char* str, char*** tokens, unsigned int* size)
{
  char token[50];
  int i = 0;
  int num_tok = 0;

  *tokens = malloc(sizeof(char*));

  while (i < strlen(str))
  {
    i = skip_whitespace(str, i);
    *tokens = realloc(*tokens, (i+1) * sizeof(char*));
    int ii = 0;
    while (ii+i < strlen(str) && str[ii+i] != ' ')
    {
      token[ii] = str[ii+i];
      ii++;
    }
    token[ii] = '\0';
    (*tokens)[num_tok] = token;
    printf("%s\n", (*tokens)[num_tok]);
    i += ii;
    num_tok++;
  }

  //i--;
  //*tokens = realloc(*tokens, i);
  *size = num_tok;
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
