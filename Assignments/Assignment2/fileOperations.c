#include <stdio.h> 
#include <stdlib.h>

int main (int argc, char *argv[])
{
    FILE *fs; 
    char buf[10];
    size_t sz; 

    fs = fopen("test.txt", "r");

    /* 
    FILE *
     fopen(const char *restrict filename, const char *restrict mode);

    The fopen() function opens the file whose name is the string pointed to by filename and associates a stream with it.
     The argument mode points to a string beginning with one of the following sequences (Additional characters may follow these sequence

     ``r''   Open text file for reading.  The stream is positioned at the beginning of the file.

     ``r+''  Open for reading and writing.  The stream is positioned at the beginning of the file.

     ``w''   Truncate to zero length or create text file for writing.  The stream is positioned at the beginning of the file.


*/

    if (fs == NULL)
    {
        perror("fopen");
        exit(1);
    }

    while(!feof(fs)){
        sz = fread((void *) buf, 9, 1, fs);
        //10 is the size 
        //1 is the nmemb wich corresponds to the elements of data 
        buf[9] = '\0';
        printf("%s", buf);
    }
    
    printf("\n");

    fclose(fs);



    return 0; 
}

