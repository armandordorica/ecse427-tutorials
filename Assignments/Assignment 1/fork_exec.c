#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_CHILDREN 4
int count = 0; 
int main (int argc, char *argv[])
{

  for (int i = 0; i < NUM_CHILDREN; i++){
  pid_t pid = fork();

  if(pid < 0){
      perror("fork failed.");
      exit(1);
  }

  else if (pid == 0){
    printf("num of times child code is executed is count: %d\n", count); 
    count++; 
    printf("inside the child's code\n");
    printf("This child's pid is %d\n", getpid() );
//Child's execution
    //by convention, the first argument passing to this array which will later be passed on to execvp is going to be
    //the name of your executable. In this case, bogosort. 
    char* args[] = {"./bogosort", "2", "1", "3", "4", "5", "6", "7", "8", "9", "10", NULL};
      execv(args[0], args);
  }
}


  //Parent
  //do clever processing 
  //Parent must wait for child to complete
  printf("Parent is now doing something amazing\n");
  printf("Parent is waiting on child process.\n");
  for (int i = 0; i < NUM_CHILDREN; i++){
    wait(NULL); //If this statement is not used here, there will be zombie processes created
  }

  return 0;
}