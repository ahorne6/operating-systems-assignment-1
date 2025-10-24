/*producer puts items on table*/
#include "../memorybuff.hpp"

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
    HANDLE fileDesc;
    const char *sharedMemPath = argv[1];
    struct sharedMem *semMemAccessor;

    fileDesc = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, 0, TABLE_SIZE, PAGE_READWRITE,  sharedMemPath);     //open memory
    
    semMemAccessor = static_cast<sharedMem*>(VirtualAlloc(NULL, sizeof(*semMemAccessor), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));

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
    
    CloseHandle(fileDesc);
    std::cout<<"goodbye producer";
    return 0;
    
}