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
#include "../memorybuff.hpp"



int main(int argc, char *argv[]){
    std::cout<<"hello world, consumer";
    HANDLE fileDesc;
    const char* sharedMemPath = argv[1];
    struct sharedMem *consumingMem;
    
    fileDesc = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, 0, TABLE_SIZE, PAGE_READWRITE,  sharedMemPath);

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

    CloseHandle(fileDesc);
    return 0;

}