#include <stdio.h> 

/*copy input ot output; 1st version*/ 
main (){
  int c; 
  int a=9; 
  c=getchar(); 
  while (c != EOF){
    putchar(c); 
    c = getchar();
    printf("%d\t", c);
  }
}