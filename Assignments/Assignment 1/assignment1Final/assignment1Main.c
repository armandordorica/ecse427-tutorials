/*------ Armando Ordorica. Student ID: 260526219 -------*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <assert.h>
#include <fcntl.h>
#include <signal.h>

#define HISTORY_SIZE 10
#define ARGS_ARRAY_SIZE 20
#define PID_BUFFER_SIZE 1000

#include "declarations.h"
#include "functions.h"

int getcmd(char *prompt, char *args[], int *bg, int *historyflag, int *outputflag, int *pipingflag, char *line1)
{
  int length, i = 0;
  char *token, *loc;
  char *line = NULL;
  size_t linecap = 0;
  // printf("%s", prompt);
  int flag = 0;
  length = getline(&line, &linecap, stdin);
  line1 = line;
  if (length <= 0)
  {
    exit(-1);
  }
  // Check if background is specified..
  if ((loc = index(line, '&')) != NULL)
  {
    *bg = 1;
    *loc = ' ';
  }
  if ((loc = index(line, '!')) != NULL)
  {
    *historyflag = 1;
    *loc = ' ';
  }
  if ((loc = index(line, '>')) != NULL)
  {
    *outputflag = 1;
  }
  if ((loc = index(line, '|')) != NULL)
  {
    *pipingflag = 1;
  }
  while ((token = strsep(&line, " \t\n")) != NULL)
  {
    for (int j = 0; j < strlen(token); j++)
      if (token[j] <= 32)
        token[j] = '\0';
    if (strlen(token) > 0)
      // adding the arguments to the history
      args[i++] = token;
  }
  return i;
}

int main(void)
{
  char *args[ARGS_ARRAY_SIZE];

  // Flags to detect the opeartors
  int bg;
  int hisflag;
  int outputflag;
  int pipingflag;
  int fd;

  // File Descriptors:
  int old_stdout;

  char *wordir;
  char *l;
  int status;
  // Allocating memory for the history and job structs
  history_t *history = (history_t *)malloc(sizeof(history_t));
  history->currentcmd = 0;

  jobList *jobs = (jobList *)malloc(sizeof(jobList));
  jobs->currentjob = 0;

  pid_t pids[PID_BUFFER_SIZE];
  while (1)
  {
    waitpid(-1, &status, WNOHANG);
    // reseting the values for the operators
    bg = 0;
    hisflag = 0;
    outputflag = 0;
    pipingflag = 0;

    int cnt = getcmd("\n ", args, &bg, &hisflag, &outputflag, &pipingflag, l);
    // add method here that copies commands to history array
    args[cnt] = NULL;

    // Populating the history array
    for (int i = 0; i < cnt; i++)
    {
      history->buffer[(history->currentcmd % 10)][i * 2] = args[i];
      history->buffer[(history->currentcmd % 10)][i * 2 + 1] = " ";
    }
    history->currentcmd = history->currentcmd + 1;
    if (bg)
    {
      for (int i = 0; i < cnt; i++)
      {
        //Mod makes it wrap around 10 entries
        jobs->buffer[(jobs->currentjob % 10)][i * 2] = args[i];
        jobs->buffer[(jobs->currentjob % 10)][i * 2 + 1] = " ";
      }
      jobs->currentjob = jobs->currentjob + 1;
    }

    if (strcmp(args[0], "exit") == 0)
    {
      exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
      chdir(args[1]);
    }
    else if (strcmp(args[0], "history") == 0)
    {
      history->currentcmd = history->currentcmd - 1;
      printHistory(history);
    }
    else if (strcmp(args[0], "jobs") == 0)
    {
      for (int i = 0; pids[i] != 0; i++)
      {
        printf("%d\n", pids[i]);
      }
      // jobs->currentjob = jobs->currentjob;
      // printJobs(jobs);
    }
    else if (strcmp(args[0], "fg") == 0)
    {
      // printf("inside fg\n");
      int bg_pid = atoi(args[1]);
      signal(SIGTTOU, SIG_IGN);
      //SIGTTOU two processes trying to access output (terminal) simultaneously
      tcsetpgrp(0, bg_pid);
      kill(bg_pid, SIGCONT);
      while (wait(&status) != bg_pid);
      tcsetpgrp(0, getpid());
      signal(SIGTTOU, SIG_DFL); 
    }
    else
    {
      pid_t pid = fork();
      if (bg)
      {
        setpgid(pid, pid);
      }

      if (pid == 0)
      {
        // Child process runs here
        if (hisflag)
        {
          execvp(retrieveCommand(history, atoi(args[0])), args);
        }
        int i = 0;
        if (outputflag)
        {
          old_stdout = dup(1);
          while (strcmp(args[i], ">") != 0)
          {
            i++;
          }
          redirect(args[i + 1]);
          args[i] = NULL;
        }
        if (pipingflag)
        {
          while (strcmp(args[i], "|") != 0)
          {
            i++;
          }
          args[i] = NULL;
          piping(args + i + 1);
        }
        execvp(args[0], args);
        exit(1);
      }
      else
      {
        // Parent process runs here
        if (bg)
        {
          for (int i = 0; i < PID_BUFFER_SIZE; i++)
          {
            if (pids[i] == 0)
            {
              pids[i] = pid;
              break;
            }
          }
          // waitpid(pid, &status, 0);
        }
      }
    }
  }
}