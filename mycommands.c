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

int grep(int num_args, char** args)
{
  if (num_args < 3)
  {
    printf("Usage: %s <file> <keyword>", args[0]);
    return 0;
  }

  FILE* fp = NULL;
  unsigned int line_number = 0;
  char line[512];

  fp = fopen(args[1], "r");
  if (fp == NULL)
  {
    perror("Could not open file");
    return 1;
  }

  while (fgets(line, 512, fp))
  {
    if (strstr(line, args[2]) != NULL)
      printf("%d: %s", line_number, line);
  }

  fclose(fp);
  return 1;
}

int cp(int num_args, char** args)
{
  if (num_args < 3)
  {
    printf("Usage: %s <file1> <file2>", args[0]);
    return 0;
  }
  FILE* f1;
  FILE* f2;
  char buffer[512];

  f1 = fopen(args[1], "rb");
  f2 = fopen(args[2], "wb");

  if (f1 == NULL || f2 == NULL)
  {
    perror("Cannot open file");
    return 1;
  }

  while(fread(buffer, sizeof(char), 512, f1) > 0)
    fwrite(buffer, sizeof(char), 512, f2);

  fclose(f1);
  fclose(f2);

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

int clear(int size, char** args)
{
  // This is almost right
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  for (int i = 0; i < w.ws_row; i++)
    printf("\n");
  return 0;
}
