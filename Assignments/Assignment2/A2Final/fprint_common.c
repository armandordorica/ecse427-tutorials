#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>   

#define BUFFER_SIZE 10
#define MY_SHM "/ARMANDO"
int fd; 

typedef struct
{
  int pages;
  int jobID;
} Job;

typedef struct
{
  /*variables for semaphores*/
  sem_t jobsInQueue;
  sem_t spotsAvailable;
  sem_t mutex;
  /*elements needed to treat the SharedMemory segment as a queue*/ 
  int jobCount;
  int head;
  int tail;
  int memorySize; 
  int numPrinters; 
  int JobIdArray[BUFFER_SIZE]; 
  int jobPages[BUFFER_SIZE]; 
} SharedMemory;

/*extern SharedMemory *attach_shared_memory(int fd); 
extern int setup_shared_memory()
By using 'extern', you are telling the compiler that whatever follows it will be found (non-static) 
at link time, don't reserve anything for it since it will be encountered later.
It's very useful if you need to share some global between modules and don't want to put / initialize it in a header.
Technically, every function in a library public header is 'extern', however labeling them as such has very 
little to no benefit, depending on the compiler. Most compilers can figure that out on their own*/

int setup_shared_memory(){
    /*shm_open() creates and opens a new, or opens an existing, POSIX shared memory object. 
    A POSIX shared memory object is in effect a handle which can be used by unrelated processes to mmap(2) 
    the same region og shared memory*/
   int fd = shm_open(MY_SHM, O_CREAT | O_RDWR, S_IRWXU);
    /*MY_SHM specifies the shared memory object to be created or opened. For portable use,
    a shared memory object should be identifies by a name of the form /somename; that is, a null-terminated
    string of up to NAME_MAX (i.e., 255) characters consisting of an initial slash, followed by one or more characters, 
    none of which are slashes
    O_CREAT | O_RDWR is a it mask created by ORing together exactly one of O_RDONLY
    or O_RDWR and any of the other flags. 
    S_IRWXU is the unix file mode (i.e. 0666)
    */  
    if(fd == -1){
        printf("shm_open() failed\n");
        exit(1);
    }
    ftruncate(fd, sizeof(SharedMemory));
    /* for ftruncate, the syntax is int
    ftruncate(int fildes, off_t length);
    This function will cause the file referenced by fildes, to
     be truncated (or extended) to length bytes in size. 
     */ 
     return fd; 
}

SharedMemory *attach_shared_memory(int fd){
    /* you need to cast this function to be able to match the shared_mem variable which is a 
    struct of type Shared*/ 
    SharedMemory *shared_mem = (SharedMemory *)mmap(
        NULL, 
        /*If addr is NULL, then the kernel chooses the address at  which  to
       create the mapping; this is the most portable method of creating a
       new mapping.  If addr is not NULL, then the kernel takes it  as  a
       hint  about where to place the mapping; on Linux, the mapping will
       be created at a nearby page boundary.  The address of the new map‐
       ping is returned as the result of the call.*/
        sizeof(SharedMemory), 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED, 
        fd, 
        0);

    /*The mmap() system call causes the pages starting at NULL and continuing for at most sizeof(Shared) bytes to be mapped from the
    object described by fd, starting at byte 0.
    Syntax is      
    
    void *
     mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

    PROT_READ  Pages may be read.
    PROT_WRITE Pages may be written.
 
    MAP_SHARED --> Share this mapping.  Updates to the mapping are visible to
              other processes mapping the same region, and (in the case of
              file-backed mappings) are carried through to the underlying
              file.  (To precisely control when updates are carried through
              to the underlying file requires the use of msync(2).)*/

    if(shared_mem == MAP_FAILED){
        printf("mmap() failed\n");
        exit(1);
    }

    return shared_mem;
}
