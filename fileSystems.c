/* file copy program. Error checking and reporting is minimal*/ 

/*This file copies one file to another file*/ 

/*include necessary header files*/
/*This code reads all of the bytes from the 
first file and copies them on the second file*/ 
#include <sys/types.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h> 

int main(int argc, char *argv[]);

#define BUF_SIZE 4096

//protection bits for output file
#define OUTPUT_MODE 0700

int main(int argc, char *argv[])
{
  int in_fd, out_fd, rd_count, wt_count; 
  char buffer[BUF_SIZE]; 

//generate a syntax error if argc is not 3*/ 
  if (argc != 3) exit(1); 

//Open the input file and create the output file
  in_fd = open(argv[1], O_RDONLY); //open the source file 
  if (in_fd < 0) exit(2); /*If the file cannot be opened, exit*/ 

  out_fd = creat(argv[2], OUTPUT_MODE); /*Create the destination file*/ 
  if (out_fd < 0) exit (3); /* If the file cannot be created, exit*/ 



  /*Copy loop */ 
  while (TRUE) {
      rd_count = read(in_fd, buffer, BUF_SIZE); /*Read a block of data*/ 

    if(rd_count <= 0) break; /*If end of file or error, exit the loop*/ 
      wt_count = write(out_fd, buffer, rd_count); /*write data*/ 
      if(wt_count <=0) exit(4); /* wt_count <=0 is an error*/
  }

  /*Close the files*/ 
  close(in_fd); 
  close(out_fd); 
  if (rd_count == 0)
    exit(0);  /*no error on last read */ 
  else
    exit(5); /*error on last read*/ 

}
