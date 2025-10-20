/* consumer takes items off table */
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "memorybuff.hpp"



int main(int argc, char *argv[]){
    int fileDesc;
    char * sharedMemPath;
    struct sharedMem *consumingMem;

    sharedMemPath = argv[1];
    fileDesc = shm_open(sharedMemPath, O_RDWR, 0);

    ftruncate(fileDesc, sizeof(*consumingMem));

    consumingMem = static_cast<sharedMem*>(CreateFileMapping(NULL, NULL, PAGE_EXECUTE_READWRITE, sizeof(*consumingMem), fileDesc, 0));

    for (int i = 4; i >= 0; --i) {
        sem_wait(&(consumingMem->full));
        sem_wait(&(consumingMem->mutex));
        int consuming_item;
        consuming_item = consumingMem->table[consumingMem->out];
        std::cout << "Consumed: " <<  consuming_item << std::endl;
  
        consumingMem->out = (consumingMem->out + 1) % TABLE_SIZE;
        sem_post(&(consumingMem->mutex));
        sem_post(&(consumingMem->empty));
    }


    //Detatch mem
    shm_unlink(sharedMemPath);


    return 0;

}