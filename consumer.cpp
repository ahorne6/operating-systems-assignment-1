/* consumer takes items off table */
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <conio.h>
#include <tchar.h>
#include <windows.h>
#include "memorybuff.hpp"



int main(int argc, char *argv[]){
    HANDLE fileDesc;
    const char* sharedMemPath = argv[1];
    struct sharedMem *consumingMem;
    

    // fileDesc = shm_open(sharedMemPath, O_RDWR, 0);
    fileDesc = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, 0, TABLE_SIZE, PAGE_READWRITE,  sharedMemPath);

    // ftruncate(fileDesc, sizeof(*consumingMem));

    // consumingMem = static_cast<sharedMem*>(CreateFileMapping(NULL, NULL, PAGE_EXECUTE_READWRITE, sizeof(*consumingMem), fileDesc, 0));
    //  consMem = static_cast<sharedMem*>(mmap(NULL, sizeof(*consMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    consumingMem = static_cast<sharedMem*>(VirtualAlloc(NULL, sizeof(*consumingMem), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));

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
    CloseHandle(fileDesc);



    return 0;

}