#include <stdio.h> 

/*copy input to output; 2nd version */

main () {
  int c; 
  while ((c = getchar()) != EOF){
    putchar(c); 
  }
}

/*The while gets a character, assigns it to c, and then it tests whether the caracter was the end-of-file signal. If it was not, the body of the while 
is executed, printing the character. The while then repeats. When the end of the input is finally reached, 
the while terminates and so does main*/ 