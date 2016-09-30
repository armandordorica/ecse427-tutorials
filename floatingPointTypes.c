#include <stdio.h>
#include <float.h>

int main() {

   printf("Storage size for float : %d \n", sizeof(float));
   printf("Minimum float positive value: %E\n", FLT_MIN );
   printf("Maximum float positive value: %E\n", FLT_MAX );
   printf("Precision value: %d\n", FLT_DIG );
   
   return 0;
}

/* sizeof() generates the size of a variable or datatype, measured 
in the number of char size storage units required for the typee.*/