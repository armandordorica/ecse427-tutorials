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
