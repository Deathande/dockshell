#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "mycommands.h"

char* ps1 = "$ ";

void get_in();
void tokenize(char*, char***, unsigned int*);
void run_cmd(char**, unsigned int);

int main(int argc, char** argv)
{
  while (1)
    get_in();
}

void get_in()
{
  char input[512];
  char buffer[512];
  char* nl;
  char** tokens;
  unsigned int num_tok;
  
  write(STDOUT_FILENO, ps1, strlen(ps1));
  read(STDIN_FILENO, buffer, 512);

  strcpy(input, buffer);
  //memset(buffer, 0, 512);
  // Strip new line from input
  if ((nl=strchr(input, '\n')) != NULL)
    *nl = '\0';
  tokenize(input, &tokens, &num_tok);
  run_cmd(tokens, num_tok);

  memset(input, 0, 512);
  free(tokens);
}

void run_cmd(char** toks, unsigned int size)
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

  //i--;
  //*tokens = realloc(*tokens, i);
  *size = i-1;
}
