#include "common.h"

int fd;
Shared* shared_mem;

int setup_shared_memory(){
    fd = shm_open(MY_SHM, O_RDWR, S_IRWXU);
    if(fd == -1){
        printf("shm_open() failed\n");
        exit(1);
    }
}

int attach_shared_memory(){
    shared_mem = (Shared*) mmap(NULL, sizeof(Shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shared_mem == MAP_FAILED){
        printf("mmap() failed\n");
        exit(1);
    }

    return 0;
}

void handler(int signo){
    int temp;
    sem_getvalue(&shared_mem->binary, &temp);
    if(temp != 1)
        sem_post(&shared_mem->binary);
    sem_getvalue(&shared_mem->resource, &temp);
    if(temp != 1)
        sem_post(&shared_mem->resource);
    exit(0);
}

int main() {
    if(signal(SIGINT, handler) == SIG_ERR)
        printf("Signal Handler Failure ..\n");
    setup_shared_memory();
    attach_shared_memory();
    while (1) {
        sem_wait(&shared_mem->binary);
        shared_mem->readcount++;
        if(shared_mem->readcount == 1)
            sem_wait(&shared_mem->resource);
        sem_post(&shared_mem->binary);
        printf("data is %d\n", shared_mem->data);
        sem_wait(&shared_mem->binary);
        shared_mem->readcount--;
        if(shared_mem->readcount == 0){
            sleep(1);
            sem_post(&shared_mem->resource);
        }
        sem_post(&shared_mem->binary);
    }

    return 0;
}
