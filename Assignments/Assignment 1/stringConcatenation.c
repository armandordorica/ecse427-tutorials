#include <stdio.h>
#include <string.h>

char* concatenate(char* tarray[], int i);

char* concatenate (char* array[], int i){
   printf("Value of array at %d is %s\n", i, array[i]); 
}

int main () {

   // char str1[12] = "Hello";
   // char str2[12] = "World";
   // char str3[12];
   // int  len ;

   // /* copy str1 into str3 */
   // strcpy(str3, str1);
   // printf("strcpy( str3, str1) :  %s\n", str3 );

   //  concatenates str1 and str2 
   // strcat( str1, str2);
   // printf("strcat( str1, str2):   %s\n", str1 );

   // /* total lenghth of str1 after concatenation */
   // len = strlen(str1);
   // printf("strlen(str1) :  %d\n", len );


   char* testArray[] = { "a", "b", "c"}; 
   printf("Value of array at %d is %s\n", 1, testArray[1]); 
   printf("Value of array at %d is %s\n", 2, testArray[2]); 
   // concatenate(testArray, 0); 
   int arrayLength = sizeof(testArray)/8;

   printf("size of array is %d\n", arrayLength);

   return 0;
}