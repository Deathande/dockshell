#include "mycommands.h"

int ls(int num_args, char** args)
{
  DIR* directory;
  char cwd[100];
  struct dirent* d_ent;

  getcwd(cwd, 100);
  directory = opendir(cwd);

  while ((d_ent = readdir(directory)) != NULL)
    printf("%s\n", d_ent->d_name);

  closedir(directory);
  
  return 0;
}

int cat(int num_args, char** args)
{
  printf("%d\n", num_args);
  if (num_args < 2)
  {
    printf("Usage: %s <filename>", args[0]);
    return 0;
  }

  FILE* fp = NULL;
  const unsigned int buffer_size = 512;
  char buff[buffer_size];

  fp = fopen(args[1], "r");
  if (fp == NULL)
  {
    perror("Could not open file");
    return 1;
  }

  while (fgets(buff, buffer_size, fp) != NULL)
    printf("%s", buff);

  fclose(fp);
  return 0;
}

int clear(unsigned int size, char** args)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  for (int i = 0; i < w.ws_row; i++)
    printf("\n");
  return 0;
}
