// How to pass a value in as a global pointer but return an answer using global data


#include <stdio.h> 
#include <stdlib.h> 

void* sum_runner(void* arg);

/*int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
*/

int main (int argc, char **argv)
{
  if(argc < 2) {
    printf("Usage %s <num>\n", argv[0]);
    exit(-1);
  }
//extracting the arguments from the command line
  long long limit = atoll (argv[1]); //atoll means ascii to long long 
}

//What this could will do is to add the numbers from 0 to 3 in a background thread. 