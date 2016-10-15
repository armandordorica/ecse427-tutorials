#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

  int fd = dup(1); 
  printf("fd: %d\n", fd);
  close(1);
  
  open("temp2.txt", O_WRONLY | O_APPEND);
  if (fork() == 0){

  close(1); 
  int n = dup(fd); 
  printf("dup(fd) is %d\n", n);
  printf("message from A\n");
  // write("hello"); 
  }
  else{  
    printf("message from B\n");
  }

}

//This will generate an output on temp2.txt with Message from B
// This will generate an output on termianl from message A
