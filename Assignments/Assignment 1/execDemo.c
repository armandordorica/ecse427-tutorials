#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int favNum=42; 

int main (int argc, char *argv[])
{
  printf("execDemo: My pid is %d.\n", getpid());

  //Different types of execL execl and execv
  //With L: comma separated arguments 
  //With V: Vector (i.e. an array of strings)
  //With P: include normal search path for executable 

  /*first come up with the arguments for your execvp. The syntax is the following: 
    int execvP(const char *file, const char *search_path, char *const argv[]); 
    The exec family of functions replaces the current process image with a new process
    image.*/ 

    /*This array is NULL terminated to be able to tell it when to stop*/
    /*The first argument will be the name of the process that we're calling*/
    /*"functions provide an array of pointers to null-
     terminated strings that represent the argument list available to the new program.
     The first argument, by convention, should point to the file name associated with the
     file being executed.  The array of pointers must be terminated by a NULL pointer."*/
  char *args[] = {"./helloExec", "Hello", "World", NULL};

  execvp(args[0], args);

/*This line of code will never be executed because execvp never returns. execvp function 
replaces everything that's running in the current process image by the program you are
now trying to run, which is helloExec*/
  printf("Farewell cruel world\n");

  return 0;
}
