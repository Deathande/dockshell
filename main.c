#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* ps1 = "$ ";

void get_in();
char** tokenize(char*);
void parse_cmd(char**);

int main(int argc, char** argv)
{
  while (1)
    get_in();
}

void get_in()
{
  char input[512];
  char buffer[512];
  char** tokens;
  
  write(STDOUT_FILENO, ps1, strlen(ps1));
  read(STDIN_FILENO, buffer, 512);
  strcpy(input, buffer);
  tokens = tokenize(input);
}

void parse_cmd(char** tokens)
{
}

char** tokenize(char* str)
{
  char** tokens;
  char* token;
  int i = 0;

  tokens = malloc(20 * sizeof(char*));

  token = strtok(str, " ");
  tokens[i] = token;
  i++;
  while (token != NULL)
  {
    token = strtok(NULL, " ");
    tokens[i] = token;
    i++;
  }

  return tokens;
}
