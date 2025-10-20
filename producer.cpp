/*producer puts items on table*/
#include "memorybuff.hpp"

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <fcntl.h>
#include <memoryapi.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>

int main(int argc, char *argv[]){
    int fileDesc;
    char *sharedMemPath;
    struct sharedMem *semMemAccessor;

    sharedMemPath = argv[1];

    fileDesc = shm_open(sharedMemPath, O_CREAT | O_EXCL | O_RDWR, 0600);      //open memory

    ftruncate(fileDesc, sizeof(*semMemAccessor));    //ensure correct sizing
    semMemAccessor = static_cast<sharedMem*>(CreateFileMapping(NULL, NULL, PAGE_EXECUTE_READWRITE, sizeof(*semMemAccessor), fileDesc, 0));

    sem_init(&(semMemAccessor->mutex), 1,1);
    
    sem_init(&(semMemAccessor->full), 1,0);
    
    sem_init(&(semMemAccessor->empty), 1, TABLE_SIZE);

    semMemAccessor->in, semMemAccessor->out = 0;

    for(int i = 4; i >= 0; --i) {
     
        sem_wait(&semMemAccessor->empty);  
        sem_wait(&semMemAccessor->mutex);  //wait for other sems to not be in use

        int randval = rand();

        std::cout << "Produced: " << randval << std::endl;

        semMemAccessor->table[semMemAccessor->in] = randval;


        semMemAccessor->in = (semMemAccessor->in + 1) % TABLE_SIZE;  //ONLY 0-TABLE SIZE (2)


        
        sem_post(&semMemAccessor->mutex); 
        sem_post(&semMemAccessor->full);
                //produced, release mutex and buffer is full
    }
    shm_unlink(sharedMemPath);


    return 0;
    
}