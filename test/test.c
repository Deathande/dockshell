#include "parsing.h"

int main(int argc, char** argv)
{
  char str[512] =  "\"This is a string\" this is a message\0";
  char** tokens;
  unsigned int size;
  tokenize(str, &tokens, &size);
  printf("size: %d\n", size);
  for (int i = 0; i < size; i++)
    printf("%s\n", tokens[i]);
}
