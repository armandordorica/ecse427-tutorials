#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){



  int fd = dup(1); 
  printf("fd: %d\n", fd);
  close(1);
  
  //need to access the part of character pointer to the string containing whatever was
  //right after > sign and put it instead of 
  open("temp2.txt", O_WRONLY | O_APPEND);
  if (fork() == 0){

  // close(1); 
  // dup(fd);   
  // int n = 
  // printf("dup(fd) is %d\n", n);
  printf("message from A\n");
  // write("hello"); 
    execvp(args[0], args);
  }
  else{  
    printf("message from B\n");
  }

}

//This will generate an output on temp2.txt with Message from B
// This will generate an output on termianl from message A
