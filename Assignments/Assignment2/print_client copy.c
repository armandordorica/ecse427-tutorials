#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/shm.h>

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
#define BUF_SIZE 100

int main (int argc, char *argv[])
{

#include "printCommon.h"


    /*shared memory id is shmid. This is the return value from shmget()*/
    //A shared memory segment is described by a control structure with a unique ID that points to an area of physical memory. 
    //the identifier of the segment is called the shmid. 
    /*The structure definition for the shared memory segment control structures and prototypes can be found in 
    <sys/shm.h> */

    /*The key argument is an access value associated with the semaphore ID. This key will be passed to shmget(), 
    which will create a shared memory segment.*/ 
    sharedMemory.size = BUF_SIZE;
    sharedMemory.key = 9876; 
    sharedMemory.id = shmget(sharedMemory.key, sharedMemory.size, 0666);
    /*Client doesn't create anything, so get rid of IPC_CREAT | */ 
    if(sharedMemory.id < 0)
    {
        /*Upon successful completion of shmget, a positive shared memory segment identifier is returned. 
        Otherwise, -1 is returned and the global variable errno is set to indicate the error*/ 
        perror("shmget");
        exit(1);
    }
    
    
    sharedMemory.address = shmat(sharedMemory.id, NULL, 0); 
    /* Basic syntax is void *shmat(int shmid, const void *shmaddr, int shmflg);

    shmat() Maps the shared memory segment associated with the shared memory identifier shmid into 
    the address space of the calling process. The address at which the segment is mapped is determined 
    by the shmaddr parameter. If it is equal to 0, the system will pick an address itself. Otherwise, 
    an attempt is made to map the shared memory segment at the address that shmaddr specifies. 
    
    Shmat returns the address at which the shared memory segment has been mapped into the calling process’ 
    address space when successful. Otherwise, a value of -1 is returned and the global variable errno is 
    set to indicate the error. */

    if(sharedMemory.address == (char *) -1)
    {
        perror("shmat");
        exit(1); 
    }

//Reads the content of the shared memory and prints it 
    for(sharedMemory.contentCounter = sharedMemory.address; *sharedMemory.contentCounter != 0; sharedMemory.contentCounter++)
        printf("%c", *sharedMemory.contentCounter);

    printf("\n");

//Shares the first character in the shared memory to an asterisk
    *sharedMemory.address = '*';

    return 0; 
} 


