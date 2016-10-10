#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

int getcmd(char *prompt, char *args[], int *background)
{
  printf("Inside getcmd function\n"); 
  int length, i=0; //length measures how long the input string into args[0] is 
  char *token, *loc; 
  char *line = NULL; 
  size_t linecap = 0; 

  printf("Prompt is: %d\n", prompt); //This prints out a specific long address that never changes regardless 
  //of what the command is. However it changes its value every time you reexecute the code 

  length = getline(&line, &linecap, stdin);
  printf("length is %d\n", length); 

  if (length <= 0) {
    exit(-1);
  }

  //check is background is specified

  if ((loc = index(line, '&')) != NULL){
    *background = 1;
    *loc = ' ';
  } else
    *background =0; 

    while ((token = strsep(&line, " \t\n")) != NULL) {
      for (int j = 0; j< strlen(token); j++)
        if(token[j] <= 32)
          token[j]= '\0';
        if (strlen(token) > 0)
          args[i++] = token;
    }

    return i;
}

int main (void)
{
  char* args[20];
  int bg;


  while(1){
    printf("inside the while loop\n\n");
    bg = 0; 
    int cnt = getcmd("\n>> ", args, &bg); 
    printf("cnt is %d\n", cnt);
    pid_t pid = fork(); 
    printf("pid %d\n\n", pid);

    if(pid ==0)
    {
      printf("args[0] = %s\n", args[0]);

       char *args[] = {"./helloExec", "Hello", "World", NULL};

  execvp(args[0], args);
    // execvp(args[0],args); 
    printf("after execvp\n");
    exit(1); 
    }else{
      int status; 
      waitpid(pid, &status, 0); //patent waits for child to complete its execution

    /*the steps can be ...: 
    (1) fork a child using fork ()
    (2) the child process will invoke execvp ()
    (3) if background is not specified, the parent will wait, otherwise parent starts the next command */ 


   }
  }
}