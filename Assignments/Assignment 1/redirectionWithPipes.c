
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "String from child to parent\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                /*If child wants to send data to the parent, 
                it should close fd0 and parent should close fd1). */

                /*If parent wants to send data to the child, it should close fd0, and the 
                child should close fd1*/  

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                //This asks the kernel to write the string to the
                // the device pointed to by file descriptor 1
                //by default, file descriptor 1 is pointing to stdout which is the screen

                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                /* read returns the number of bytes read (zero indicates end of file)
                 and the file position is advanced by this number*/
                /*fd[0] is the file descriptor of the file
                readbuffer is the buffer where the read data is to be stored
                sideof(readbuffer) is the number of bytes to be read from the file*/ 
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}
