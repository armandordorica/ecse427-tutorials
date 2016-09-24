#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20
/*print Fahrenheit - Celsius table */ 
main ()
{
  int fahr; 
  for (fahr=LOWER; fahr<=UPPER; fahr = fahr +STEP){
    printf("%3d %6.1f\n", fahr, (fahr-32)*(5.0/9.0));
  }
}