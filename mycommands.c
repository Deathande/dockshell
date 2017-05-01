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
  char time_b[26];
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
  printf("File: %s\n", args[1]);
  printf("Size: %d\tBlocks: %d\tIO Blocks: %d\n",
         (int)buffer->st_size, 
         (int)buffer->st_blocks,
         (int)buffer->st_blksize);
  printf("Device: %d\tInode: %d\tLinks: %d\n",
          (int)buffer->st_dev,
          (int)buffer->st_ino,
          (int)buffer->st_nlink);
  printf("Access:");
  printf((S_ISDIR(buffer->st_mode)) ? "d" : "-");
  printf( (buffer->st_mode & S_IRUSR) ? "r" : "-");
  printf( (buffer->st_mode & S_IWUSR) ? "w" : "-");
  printf( (buffer->st_mode & S_IXUSR) ? "x" : "-");
  printf( (buffer->st_mode & S_IRGRP) ? "r" : "-");
  printf( (buffer->st_mode & S_IWGRP) ? "w" : "-");
  printf( (buffer->st_mode & S_IXGRP) ? "x" : "-");
  printf( (buffer->st_mode & S_IROTH) ? "r" : "-");
  printf( (buffer->st_mode & S_IWOTH) ? "w" : "-");
  printf( (buffer->st_mode & S_IXOTH) ? "x" : "-");
  printf("  Uid: (%d/%s) ", buffer->st_uid, (char*)getpwuid(buffer->st_uid)->pw_name);
  printf("  Gid: (%d/%s)", buffer->st_gid, (char*)getgrgid(buffer->st_gid)->gr_name);
  printf("\n");
  strftime(time_b, 26, "%Y-%m-%d %H:%M:%S", localtime(&buffer->st_atime));
  printf("Access: %s\n", time_b);
  strftime(time_b, 26, "%Y-%m-%d %H:%M:%S", localtime(&buffer->st_mtime));
  printf("Modify: %s\n", time_b);
  strftime(time_b, 26, "%Y-%m-%d %H:%M:%S", localtime(&buffer->st_ctime));
  printf("Change: %s\n", time_b);
  printf("Birth: %d\n", (int)birthtime(buffer));

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
      waitpid(pid, &status, WNOHANG);
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

  FILE* fp1;
  FILE* fp2;
  unsigned int ln1 = 0;
  unsigned int ln2 = 0;
  char** text1;
  char** text2;

  fp1 = fopen(args[1], "r");
  fp2 = fopen(args[2], "r");

  if (fp1 == NULL)
  {
    printf("Error opening file: %s", args[1]);
    return 1;
  }

  if (fp2 == NULL)
  {
    printf("Error opening file: %s", args[2]);
    return 1;
  }

  text1 = malloc(sizeof(char*) * 500);
  text2 = malloc(sizeof(char*) * 500);

  for (int i = 0; i < 500; i++)
  {
    text1[i] = malloc(sizeof(char) * buffer_size);
    text2[i] = malloc(sizeof(char) * buffer_size);
  }
  
  while (fgets(text1[ln1], buffer_size, fp1))
    ln1++;
  while(fgets(text2[ln2], buffer_size, fp2))
    ln2++;

  int** lcs_len;

  lcs_len = malloc(sizeof(int*) * ln1+1);
  for (int i = 0; i < ln1+1; i++)
    lcs_len[i] = malloc(sizeof(int) * ln2+1);

  for (int i = 0; i < ln1+1; i++)
    lcs_len[0][i] = 0;
  for (int i = 0; i < ln2+1; i++)
    lcs_len[i][0] = 0;

  for (int i = 1; i < ln1+1; i++)
  {
    for (int j = 1; j < ln2+1; j++)
    {
      int cmp = strcmp(text1[i-1], text2[j-1]);
      if (cmp == 0)
      {
        lcs_len[i][j] = lcs_len[i-1][j-1]+1;
      }
      else
      {
        if (lcs_len[i-1][j] < lcs_len[i][j-1])
        {
          lcs_len[i][j] = lcs_len[i][j-1];
        }
        else
        {
          lcs_len[i][j] = lcs_len[i-1][j];
        }
      }
    }
  }

  /* Output table */
  for (int i = 0; i < ln1+1; i++)
  {
    for (int j = 0; j < ln2+1; j++)
    {
      printf("%d ", lcs_len[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  print_table(lcs_len, text1, text2, ln1, ln2);

  return 0;
}

int fork_test(int size, char** args)
{
  pid_t pid = fork();
  if (pid != 0)
    printf("%d\n", pid);
  else
  {
    sleep(10);
    exit(0);
  }
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
  int status = 0;
  waitpid(pid, &status, 0);
  //printf("%d\n", WIFEXITED(status));
  return 0;
}
