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
    printf("Usage: %s <keyword> <file>", args[0]);
    return 0;
  }
  //printf("%s\n", args[1]);

  FILE* fp = NULL;
  unsigned int line_number = 0;
  char line[512];
  char ss[150] = "\0";
  int index = 2;

  for (int i = index; i < num_args; i++)
  {
    fp = fopen(args[i], "r");
    printf("%s\n", args[i]);
    if (fp == NULL)
    {
      perror("Could not open file");
      return 1;
    }

    while (fgets(line, 512, fp))
    {
      if (strstr(line, ss) != NULL)
      {
        printf("%d: %s", line_number, line);
      }
    }
    printf("\n");
    fclose(fp);
  }
  return 0;
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
  //printf("%d\n", num_args);
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
  printf("\033[2J\033[0;0f");
  fflush(stdout); // may not clear riht away without clearing the buffer
  return 0;
}

int cd (int size, char** args)
{
  if (size < 2)
  {
    printf("too few arguments");
    return 0;
  }
  if(chdir(args[1]) < 0)
    return 1;
  return 0;
}
