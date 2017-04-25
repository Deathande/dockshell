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
  char commands[60][50] = {
    "LD_LIBRARY_PATH\0",
    "CSF_UnitsDefinition\0",
    "CSF_GraphicShr\0",
    "TERMINATOR_UUID\0",
    "ANDROID_HOME\0",
    "XDG_MENU_PREFIX\0",
    "CSF_EXCEPTION_PROMPT\0",
    "LANG\0",
    "DISPLAY\0",
    "OLDPWD\0",
    "COLORTERM\0",
    "MOZ_PLUGIN_PATH\0",
    "CSF_IGESDefaults\0",
    "CSF_XCAFDefaults\0",
    "XDG_VTNR\0",
    "GIO_LAUNCHED_DESKTOP_FILE_PID\0",
    "SSH_AUTH_SOCK\0",
    "CSF_STEPDefaults\0",
    "XDG_SESSION_ID\0",
    "CSF_XSMessage\0",
    "USER\0",
    "QT_QPA_PLATFORMTHEME\0",
    "PWD\0",
    "HOME\0",
    "TMUX\0",
    "CSF_PluginDefaults\0",
    "XDG_DATA_DIRS\0",
    "TERMINATOR_DBUS_NAME\0",
    "CSF_StandardDefaults\0",
    "GJS_DEBUG_OUTPUT\0",
    "CSF_StandardLiteDefaults\0",
    "MMGT_CLEAR\0",
    "CSF_UnitsLexicon\0",
    "GTK_MODULES\0",
    "TERMINATOR_DBUS_PATH\0",
    "MAIL\0",
    "WINDOWPATH\0",
    "CSF_XmlOcafResource\0",
    "VTE_VERSION\0",
    "TERM\0",
    "SHELL\0",
    "XDG_CURRENT_DESKTOP\0",
    "ANDROID_SWT\0",
    "CASROOT\0",
    "GIO_LAUNCHED_DESKTOP_FILE\0",
    "TMUX_PANE\0",
    "XDG_SEAT\0",
    "SHLVL\0",
    "GNOME_DESKTOP_SESSION_ID\0",
    "LOGNAME\0",
    "DBUS_SESSION_BUS_ADDRESS\0",
    "XDG_RUNTIME_DIR\0",
    "CSF_MDTVTexturesDirectory\0",
    "XAUTHORITY\0",
    "PATH\0",
    "CSF_LANGUAGE\0",
    "GJS_DEBUG_TOPICS\0",
    "SESSION_MANAGER\0",
    "CSF_SHMessage\0",
    "_\0"
  };
  char* out;

  for(int i = 0; i < 60; i++)
  {
    out = getenv(commands[i]);
    printf("%s=%s\n", commands[i], out);
  }
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

// TODO: Needs work
int timeout(int size, char** args)
{
  pid_t pid = fork();
  if (pid == 0)
  {
    // child
    exit(0);
    char* child_args[50];
    for (int i = 2; i < size; i++)
    {
      child_args[i-2] = args[i];
      printf("%s\n", child_args[i-2]);
    }
    parse(child_args, size - 2);
    while (1) {}
  }
  else
  {
    // parent
    int time;
    time = strtol(args[1], NULL, 10);
    sleep(time);
    int status;
    pid_t c_status = waitpid(pid, &status, WNOHANG);
    printf("c_status: %d\n", c_status);
    printf("status: %d\n", status);
    if (c_status == 0)
    {
      kill(pid);
      printf("Child terminated\n");
    }
  }
  if (pid == 0)
    printf("here\n");
  return 0;
}

int diff (int size, char** args)
{
  if (size < 3)
  {
    printf("Too few arguments\n");
    return 0;
  }
  FILE* fp1;
  FILE* fp2;
  unsigned int ln = 0;
  unsigned int ln1 = 0;
  unsigned int ln2 = 0;
  char line[512];

  fp1 = fopen(args[1], "r");
  fp2 = fopen(args[2], "r");

  while (fgets(line, 512, fp1))
    ln1++;
  while (fgets(line, 512, fp2))
    ln2++;

  return 0;
}
