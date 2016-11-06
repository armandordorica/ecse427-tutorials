#include "fprint_common.h"

#define SECONDS_PER_PAGE 1 

Job myjob; 
SharedMemory *mySharedMemory; 
int fd;
int errno;
int jobId; 
int numPages; 

void getJob()
{
    printf("Enter number of pages to print: \n"); 
    scanf("%d", &numPages); 
}

void enqueue(){
    int index = (mySharedMemory->tail) % (mySharedMemory->memorySize); 
    mySharedMemory->jobPages[index] = numPages; 
    mySharedMemory->tail = i+1; 
    return mySharedMemory->jobIdArray[index] = mySharedMemory->jobCount++; 
}


int main()
{
//set up shared memory by attaching the corresponding file descriptor to it 
 fd = setup_shared_memory(); 
 mySharedMemory = attach_shared_memory(fd); 
 
 //retrieve job parameters from user input through terminal 
 getJob(); 

 //perform semaphore operations to ensure mutual exclusion and add job to queue
 sem_wait(&mySharedMemory->spotsAvailable); /*decrease spots available in buffer*/ 
 sem_wait(&mySharedMemory->mutex); /*Decrease the mutex*/ 
 /*enqueue()*/ 
 jobId = enqueue(); 

 sem_post(&mySharedMemory->mutex); /*increase the mutex*/
 sem_post(&mySharedMemory->jobsInQueue) /*Increase number of jobs in queue*/ 

 printf("Client request:\n %d Pages to print: \n Job ID: %d ", numPages, jobId);


/*   The munmap() system call deletes the mappings  for  the  specified
       address  range,  and causes further references to addresses within
       the range to generate invalid memory references.   The  region  is
       also  automatically  unmapped  when the process is terminated.  On
       the other hand, closing the file descriptor  does  not  unmap  the
       region.

       The  address  addr must be a multiple of the page size (but length
       need not be).  All pages containing a part of the indicated  range
       are unmapped, and subsequent references to these pages will gener‐
       ate SIGSEGV.  It is not an error if the indicated range  does  not
       contain any mapped pages.
*/ 

munmap(MY_SHM, sizeof(SharedMemory)); 
 exit(0); 




}