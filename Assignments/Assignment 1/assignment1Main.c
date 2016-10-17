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

#define HISTORY_SIZE 10
#define ARGS_ARRAY_SIZE 20
#define PID_BUFFER_SIZE 1000

typedef struct
{
  char* buffer[HISTORY_SIZE][ARGS_ARRAY_SIZE];
  int currentcmd;
} history_t;

typedef struct
{
  char* buffer[HISTORY_SIZE][ARGS_ARRAY_SIZE];
  int currentjob;
} jobList;

  // Function Declarations:
  void printCommand (history_t* history);
  char* concatenate (char* array[], char* commandList);
  void add_spaces(char *dest, int num_of_spaces);
  void redirect (char* file);
  void piping (char* piping_args[]);
  char* retrieveCommand (history_t* history, int i);


history_t* history;
jobList* jobs;


  char* concatenate (char* array[], char* command)
  {
    int i = 0;
    while (array[i] != NULL && array[i+1]!= NULL)
    {
      //printf("Elements of array %s\n", array[i] );
      strcat(command, array[i]);
      i++;
    }
    return command;
  }

  char* retrieveCommand (history_t* history, int i)
  {
        char* historyCommand = (char*) malloc(PID_BUFFER_SIZE *sizeof(char));
        return concatenate(history->buffer[(i-1)%10], historyCommand);
  }

  void printHistory (history_t* history)
  {
      for (int i = (history->currentcmd - (history->currentcmd%10)); i < history->currentcmd; i++)
      {
        char* historyList = (char*) malloc(PID_BUFFER_SIZE *sizeof(char));
        printf("Command %d : %s \n",i+1, concatenate(history->buffer[i%10], historyList));
      }
  }

  void printJobs (jobList* jobs)
  {
      for (int i = (jobs->currentjob - (jobs->currentjob%10)); i < jobs->currentjob; i++)
      {
        char* jobList = (char*) malloc(PID_BUFFER_SIZE *sizeof(char));
        printf("Command %d : %s \n",i+1, concatenate(jobs->buffer[i%10], jobList));
      }
  }

  void redirect (char* file)
  {
    close(1);
    open (file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  }

  void piping (char* piping_args[])
  {
    pid_t ppid; 
    int pipefdes[2]; //pipe file descriptor

    pipe(pipefdes);

    if((ppid = fork()) == 0){
      dup2(pipefdes[0], 0); 
      close(pipefdes[1]); 
      execvp(piping_args[0], piping_args);
    }
    else{
      dup2(pipefdes[1], 1);
      close(pipefdes[0]); 
    }
  }

int getcmd(char *prompt, char *args[], int *bg, int *historyflag, int *outputflag, int *pipingflag, char* line1)
{
   int length, i = 0;
   char *token, *loc;
   char *line = NULL;
   size_t linecap = 0;
   // printf("%s", prompt);
   int flag = 0;
   length = getline(&line, &linecap, stdin);
   line1 = line;
   if (length <= 0) {
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
   while ((token = strsep(&line, " \t\n")) != NULL) {
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

   char* wordir;
   char* l;
     int status;
   // Allocating memory for the history and job structs 
   history_t* history = (history_t*) malloc(sizeof(history_t));
   history->currentcmd = 0;

   jobList* jobs = (jobList*) malloc(sizeof(jobList));
   jobs->currentjob = 0;


   pid_t pids[PID_BUFFER_SIZE];
   while(1)
   {
     waitpid(-1, &status, 0);
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
       history->buffer[(history->currentcmd%10)][i*2] =  args[i];
       history->buffer[(history->currentcmd%10)][i*2+1] = " ";
     }
     history->currentcmd = history->currentcmd + 1;
     if (bg)
       {
          for (int i = 0; i < cnt; i++)
         {
          //Mod makes it wrap around 10 entries 
           jobs->buffer[(jobs->currentjob%10)][i*2] =  args[i];
           jobs->buffer[(jobs->currentjob%10)][i*2+1] = " ";
         }
           jobs->currentjob = jobs->currentjob + 1;
       }

     pid_t pid = fork();

     if (pid == 0)
     {
      // Child process runs here
      if (hisflag)
      {
        execvp(retrieveCommand (history, atoi(args[0])),args);
      }
      int i = 0;
      if (outputflag)
        {
        old_stdout = dup(1);
        while (strcmp(args[i], ">") != 0)
        {
          i++;
        }
        redirect(args[i+1]);
        args[i] = NULL;
      }
      if (pipingflag)
        {
          while (strcmp(args[i], "|") != 0)
        {
          i++;
        }
          args[i] = NULL; 
          piping(args+i+1); 
        }
       execvp(args[0],args);
       exit(1);
     }
     else
     {
       // Parent process runs here
      if (bg)
        {
          waitpid(pid,&status,0);
        } 
        else
        {
       if (strcmp(args[0],"exit")==0)
       {
           exit(0);
       }
       if (strcmp(args[0],"cd")==0)
       {
           chdir(args[1]);
       }
       if (strcmp(args[0],"history")==0)
       {
         history->currentcmd = history->currentcmd - 1;
         printHistory(history);
       }
       if (strcmp(args[0],"jobs")==0)
       {
         jobs->currentjob = jobs->currentjob;
         printJobs(jobs);
       }
     }
   }
   }
}