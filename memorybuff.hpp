#ifndef MEMORYBUFF_HPP
#define  MEMORYBUFF_HPP
    #include <stdlib.h>
    #include <semaphore.h>
    #include <memoryapi.h>

    #define TABLE_SIZE 2

    struct sharedMem {

        int table[TABLE_SIZE];

        int in;
        int out;

        sem_t mutex;
        sem_t empty;
        sem_t full;

    };


#endif