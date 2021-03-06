#include "common.h"
#include <unistd.h>

int fd;
int errno;
Shared* shared_mem;

int setup_shared_memory(){
    /*shm_open() creates and opens a new, or opens an existing, POSIX shared memory object. 
    A POSIX shared memory object is in effect a handle which can be used by unrelated processes to mmap(2) 
    the same region og shared memory*/
    fd = shm_open(MY_SHM, O_CREAT | O_RDWR, S_IRWXU);
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
    ftruncate(fd, sizeof(Shared));
    /* for ftruncate, the syntax is int
    ftruncate(int fildes, off_t length);
    This function will cause the file referenced by fildes, to
     be truncated (or extended) to length bytes in size. 
     */ 

}

int attach_shared_memory(){
    /* you need to cast this function to be able to match the shared_mem variable which is a 
    struct of type Shared*/ 
    shared_mem = (Shared*)  mmap(NULL, sizeof(Shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
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

    return 0;
}

int init_shared_memory() {
    shared_mem->data = 0;
    shared_mem->readcount = 0;
    sem_init(&(shared_mem->resource), 1, 1);
    sem_init(&(shared_mem->binary), 1, 1);
}

int main() {
    setup_shared_memory();
    attach_shared_memory();

    init_shared_memory();
    
    while (1) {
        sem_wait(&shared_mem->resource);
        printf("changing data from %d\n", shared_mem->data);
        shared_mem->data = shared_mem->data + 1;
        sleep(1);
        shared_mem->data = shared_mem->data * 2;
        printf("to %d\n", shared_mem->data);
        sem_post(&shared_mem->resource);
        sleep(1);
    }

    return 0;
}
