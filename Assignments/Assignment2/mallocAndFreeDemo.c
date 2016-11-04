#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main (int argc, char *arv[])
{
    char *ptr; 
    //variable to hold the address of the allocated memory 

    ptr = (char *)malloc(24); 
    //ask the OS to allocate memory for us. Pass the number of bytes to be. 
    //in this case malloc returns a void pointer, so we can 
    //pointer cast it to make it match with ptr, which is a character
    //pointer itself. 

    /*check if malloc successfully allocated 24 bytes of memory for the system*/ 
    if(ptr == NULL){
        printf("Failed to get or allocate memory"); 
        exit(1);
    } 

    //copy a string into ptr
    strcpy(ptr, "Hello there!");

    printf("ptr: %s\n", ptr);
    free(ptr); //release 

//use realloc to reallocate the memory or change the size of 
//the buffer you're trying to use

    return 0; 
}