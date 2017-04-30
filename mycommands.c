#include "mycommands.h"

extern char** environ;

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
  // This is the character sequence that will clear the terminal
  printf("\033[2J\033[0;0f");
  fflush(stdout); // may not clear riht away without clearing the buffer
  return 0;
}

/* TODO: Implement `cd ~` */
int cd (int size, char** args)
{
  if (size < 2)
  {
    printf("too few arguments");
    return 0;
  }
  if (strtok(args[1], "~") == 0)
    args[1] = getenv("HOME");
  if(chdir(args[1]) < 0)
    return 1;
  return 0;
}

int mkdir_builtin (int size, char** args)
{
  if (size < 2)
  {
    printf("Too few arguments\n");
    return 0;
  }
  if (mkdir(args[1], 0777) < 0)
  {
    printf("Failed to create directory %s\n", args[1]);
    return -1;
  }
  return 0;
}

int rmdir_builtin (int size, char** args)
{
  if (size < 2)
  {
    printf("Too few arguments\n");
    return 0;
  }
  if (rmdir(args[1]) < 0)
  {
    printf("Failed to remove directory %s\n", args[1]);
    return -1;
  }
  return 0;
}

int stat_builtin (int size, char** args)
{
  struct stat* buffer;
  buffer = malloc(sizeof(struct stat));
  if (size < 2)
  {
    printf("Too few arguments\n");
    return 0;
  }
  if (stat(args[1], buffer) < 0)
  {
    printf("could not retrieve file info\n");
    return -1;
  }
  /*printf("File: %s\n
          Size: %d            Blocks: %d           IO Blocks: %d\n
          Device: %");*/
  printf("File: %s\n", args[1]);
  printf("Size: %d Blocks: %d IO Blocks: %d\n",
         (int)buffer->st_size, 
         (int)buffer->st_blocks,
         (int)buffer->st_blksize);
  printf("Device: %d Inode: %d Links: %d\n",
          (int)buffer->st_dev,
          (int)buffer->st_ino,
          (int)buffer->st_nlink);
  printf("Access:\n");
  // TODO: More to this...
  return 0;
}

int sleep_builtin(int size, char** args)
{
  if (size < 2)
  {
    printf("Please specify a time\n");
    return 0;
  }
  unsigned int time;
  time = strtol(args[1], NULL, 10);
  return sleep(time);
}

int env( int num_args, char** args)
{
  int i = 0;
  while (environ[i])
    printf("%s\n", environ[i++]);
  return 0;
}

int kill_builtin(int size, char** args)
{
  if (size < 2)
  {
    printf("Please specify a pid\n");
    return 0;
  }
  unsigned int pid;
  pid = strtol(args[1], NULL, 10);
  return kill(pid, SIGKILL);
}

int timeout(int size, char** args)
{
  pid_t pid = fork();
  if (pid == 0)
  {
    // child
    char* child_args[50];
    for (int i = 2; i < size; i++)
    {
      child_args[i-2] = args[i];
    }
    parse(child_args, size - 2);
    exit(0);
  }
  else
  {
    // parent
    int time;
    time = strtol(args[1], NULL, 10);
    for (int i = 0; i < time; i++)
    {
      sleep(1);
      int status;
      pid_t c_status = waitpid(pid, &status, WNOHANG);
      if (WIFEXITED(status))
      {
        status = 100;
        return 0;
      }
    }
    kill(pid, SIGKILL);
  }
  return 0;
}

int diff (int size, char** args)
{
  if (size < 3)
  {
    printf("Too few arguments\n");
    return 0;
  }

  const unsigned int buffer_size = 512;
  const unsigned int up          = 1;
  const unsigned int left        = 2;
  const unsigned int diag        = 3;

  FILE* fp1;
  FILE* fp2;
  unsigned int ln1 = 0;
  unsigned int ln2 = 0;
  char line1[buffer_size];
  char line2[buffer_size];

  fp1 = fopen(args[1], "r");
  fp2 = fopen(args[2], "r");
  if (fp1 == NULL)
  {
    printf("Error opening %s\n", args[1]);
    return -1;
  }
  if (fp2 == NULL)
  {
    printf("Error opening %s\n", args[2]);
    return -1;
  }

  while (fgets(line1, buffer_size, fp1))
    ln1++;
  while (fgets(line1, buffer_size, fp2))
    ln2++;

  unsigned int lcs_length[ln1+1][ln2+1];
  unsigned int trace[ln1+1][ln2+1];
  char text1[ln1][200];
  char text2[ln2][200];

  // fp1 is top
  for (int i = 0; i < ln1+1; i++)
  {
    lcs_length[i][0] = 0;
    trace[i][0] = 0;
  }

  // fp2 is left
  for (int i = 0; i < ln2+1; i++)
  {
    lcs_length[0][i] = 0;
    trace[0][i] = 0;
  }

  rewind(fp1);
  rewind(fp2);

  for (int i = 1; i < ln1+1; i++)
  {
    fgets(line1, buffer_size, fp1);
    strcpy(text1[i-1], line1);
    //text1[i-1] = line1;
    for (int j = 1; j < ln2+1; j++)
    {
      fgets(line2, buffer_size, fp2);
      //text2[j-1] = line2;
      strcpy(text2[j-1], line2);
      int cmp = strcmp(line1, line2);
      if (cmp == 0)
      {
        trace[i][j] = diag;
        lcs_length[i][j] = lcs_length[i-1][j-1] + 1;
        printf("%d ", lcs_length[i][j]);
      }
      else if (lcs_length[i-1][j] >= lcs_length[i][j-1])
      {
        lcs_length[i][j] = lcs_length[i-1][j];
        printf("%d ", lcs_length[i][j]);
        trace[i][j] = up;
      }
      else
      {
        lcs_length[i][j] = lcs_length[i][j-1];
        //printf("%d ", lcs_length[i][j]);
        trace[i][j] = left;
      }
    }
    printf("\n");
  }

  int index_i = ln1;
  int index_j = ln2;
  char output[(ln1 > ln2) ? ln1 : ln2][buffer_size];

  while (trace[index_i][index_j] != 0)
  {
    int direction = trace[index_i][index_j];
    if (direction == up)
    {
      //printf("i: %d j: %d\n", index_i, index_j);
      printf("%s\n-----\n%s\n\n", text1[index_i-1], text2[index_j-1]);
      //sprintf(output[(ln1 < ln2) ? ln1 : ln2], "%s\n---%s\n", text1[index_i], text2[index_j]);
      index_i--;
    }
    else if (direction == left)
    {
      //printf("i: %d j: %d\n", index_i, index_j);
      printf("%s\n-----%s\n", text1[index_i-1], text2[index_j-1]);
      //sprintf(output[(ln1 < ln2) ? ln1 : ln2], "%s\n---%s\n", text1[index_i], text2[index_j]);
      index_j--;
    }
    else
    {
      //printf("here\n");
      //output[(ln1 < ln2) ? ln1 : ln2][0] = '\0';
      index_i--;
      index_j--;
    }
  }

  printf("%d\n", (ln1 > ln2) ? ln1:ln2);
  for (int i = (ln1 > ln2) ? ln1 : ln2; i > 0; i--)
    printf("%s", output[i]);

  return 0;
}

int wait_builtin(int size, char** args)
{
  if (size < 2)
  {
    printf("Please specify a process ID\n");
    return 0;
  }
  int pid = strtol(args[1], NULL, 10);
  int status;
  printf("%d\n", pid);
  printf("%d\n", WNOHANG);
  return waitpid(pid, &status, 0);
  printf("%d\n", status);
}
