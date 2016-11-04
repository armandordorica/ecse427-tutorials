#include <stdio.h> 
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/mman.h>
#include <string.h>


int main (int argc, char *argv[])
{

    int fd; 
    struct stat mystat;
    void *pmap; //we assign it to void because this is the type that mmap returns 

    fd = open("test.txt", O_RDWR);

    if(fd == -1){
        perror("open");
        exit(1);
    }

    if(fstat(fd, &mystat) < 0){
        perror("fstat");
        close(fd);
        exit(1);
    }

    pmap = mmap(0, mystat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //st_syze refers to the size of the struct which goes into size_t len 
    /*The mmap() system call causes the pages starting at addr and continuing for at most len bytes to be mapped from the
     object described by fd, starting at byte offset offset.*/

    /*
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

    if(pmap == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        exit(1);
    }

    /*The C library function char *strncpy(char *dest, const char *src, size_t n) 
    copies up to n characters from the string pointed to, by src to dest. In a case 
    where the length of src is less than that of n, the remainder of dest will be 
    padded with null bytes.*/

    strncpy(pmap, "That", 4);

    close(fd);

    return 0; 
}