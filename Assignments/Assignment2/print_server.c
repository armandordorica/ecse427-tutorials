#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
/*Print server should do three things: 
1. Create a bounded buffer (a shared memory segment)
2. Maintain a bounded buffer (attach the shared memory segment)
3. Manage associated semaphores in a shared memory area (initialize the semaphore and put it in
shared memory)

if(buffer!=NULL){
    jobIsAvailable = true; 
}

while(1){
if(!jobIsAvailable){ 
    sleep(); 
}
if(jobIsAvailable){ 
    wakeUp(); 
    printJob(); 
}

printJob(job.duration){ 
    sleep(job.duration); 
}

}
*/ 
/*It is responsible for creating and maintaining a bounded buffer and associated semaphores in a shared memory area*/

//Defining the size of the shared memory


int main (int argc, char *argv[])
{

   #include "printCommon.h"



    /*writing something to the shared memory*/ 
    memcpy(sharedMemory.address, "Hello World", 11); 
    sharedMemory.contentCounter = sharedMemory.address; 
    sharedMemory.contentCounter += 11; 

//Add a null or a zero at the end of the string contained in our shared memory
    *sharedMemory.contentCounter = 0; 

    while(*sharedMemory.address != '*')
    sleep(1); 

    return 0; 
} 


