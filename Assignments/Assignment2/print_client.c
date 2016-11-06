

/*
while(1){ }
if(numJobs = BUF_SIZE){ 
    fullBuffer = true; 
}

if(fullBuffer){ 
    sleep(); 
}


if(){

}

} 
*/ 

//Defining the size of the shared memory

int main (int argc, char *argv[])
{

#include "printCommon.h"



//Reads the content of the shared memory and prints it 
    for(sharedMemory.contentCounter = sharedMemory.address; *sharedMemory.contentCounter != 0; sharedMemory.contentCounter++)
        printf("%c", *sharedMemory.contentCounter);

    printf("\n");

//Shares the first character in the shared memory to an asterisk
    *sharedMemory.address = '*';

    return 0; 
} 


