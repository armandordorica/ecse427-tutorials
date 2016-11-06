#include "fprint_common.h"

#define SECONDS_PER_PAGE 1 

Job myjob; 
SharedMemory *mySharedMemory; 
int fd;
int errno;
int printerId; 

void initialize_shared_memory(int memorySize){ 
    printf("Setting up shared memory with %d slots\n", memorySize); 
    mySharedMemory->memorySize = memorySize; 
    mySharedMemory->head=0; 
    mySharedMemory->tail=0; 
    mySharedMemory->jobCount=0;
    mySharedMemory->numPrinters = 0; 
    //missing:  mem->printerCount = 0;
    sem_init(&(mySharedMemory->jobsInQueue), 1, 0); 
    sem_init(&(mySharedMemory->spotsAvailable), 1, memorySize); 
    sem_init(&(mySharedMemory)->mutex, 1, 1); 
}

void dequeue()
{
    /*returnValue = queue[index]; 
      queue.index = queue.index-1; 
      return returnValue;   
    */
    int index = (mySharedMemory->head) % (mySharedMemory->memorySize); 
    myjob.jobID = mySharedMemory->jobIdArray[index]; 
    myjob.pages = mySharedMemory->jobPages[index]; 
    mySharedMemory->head = index + 1; 
}

void printJob()
{
     /*
        print_a_msg(&job);
        duration of job, job ID, and source of job are printed
        */
    printf("Job duration: %d seconds. \nJob ID is: %d .\nSource printer: %d\n.", myjob.pages, myjob.jobID, printerId); 
    printf("Printing...\n");
    sleep(SECONDS_PER_PAGE * myjob.pages); 
    printf("Job ID: %d, Source printer: %d COMPLETED\n...", myjob.jobID, printerId); 
}

void removePrinter(int n){
    //decrease number of printers in my shared memory
    mySharedMemory->numPrinters--; 

    if(mySharedMemory->numPrinters == 0){ 
        shm_unlink(MY_SHM); 
        /*The shm_unlink() function performs the converse operation, removing an object previously  created  by
       shm_open().
       This is to remove the POSIX shared memory object created by shm_open() in the int setup_shared_memory() function
       in the fprint_common.c file
       */ 
       printf("Number of printers active is: 0.\n Clearing shared memory...\n"); 
    }
    else {
        munmap(MY_SHM, sizeof(SharedMemory));
    }
    exit(0); 
}

int main(int argc, char *argv[])
{

    signal(SIGINT, removePrinter); 
    fd = setup_shared_memory(); 
    mySharedMemory = attach_shared_memory(fd);

    if (mySharedMemory->numPrinters == 0)
    {
        int memorySize = BUFFER_SIZE;

        if(argc > 1)
        {
            memorySize = atoi(argv[1]); 
        }
        else 
        {
            printf("Memory size was not specified. The fault memory size will be set to %d slots.\n", BUFFER_SIZE);
        }
        initialize_shared_memory(memorySize);
    }

    else if (argc > 1)
    { 
        printf("Cannot reinitialize memory size. Another printer has already set it to %d slots.\n", mySharedMemory->memorySize);
    }

    printerId = mySharedMemory->numPrinters++; 

    printf("Printer with ID %d\t has been initialized.\n", printerId); 



    while(1){
        /* take_a_job(&job)
        Decrease the number of jobsInQueue 
        Decrease mutex
        dequeue(); 
        increase mutex
        Increase the number of remaining spots available in queue 
        */ 
        sem_wait(&mySharedMemory->jobsInQueue); 
        sem_wait(&mySharedMemory->mutex);
        dequeue(); 
        sem_post(&mySharedMemory->mutex); 
        sem_post(&mySharedMemory->spotsAvailable); 

        /*
        print_a_msg(&job);
        duration of job, job ID, and source of job are printed
        */

        printJob(); 
    }

    return 0;

}
