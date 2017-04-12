#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "parsing.h"

char* ps1 = "$ ";

int main(int argc, char** argv)
{
  while (1)
  {
    char input[512];
    char buffer[512];
    char* nl;
    char** tokens;
    unsigned int num_tok;
  
    write(STDOUT_FILENO, ps1, strlen(ps1));
    read(STDIN_FILENO, buffer, 512);

    strcpy(input, buffer);
    // Strip new line from input
    if ((nl=strchr(input, '\n')) != NULL)
      *nl = '\0';
    tokenize(input, &tokens, &num_tok);
    printf("%s\n", tokens[0]);
    parse(tokens, num_tok);

    memset(input, 0, 512);
    free(tokens);
  }
}
