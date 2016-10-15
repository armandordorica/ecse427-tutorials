#include <stdio.h> 
#include <unistd.h>

main () {

int i; 
i=10; 

if(fork() == 0) i+=20; 
printf("%d\n", i); 

}