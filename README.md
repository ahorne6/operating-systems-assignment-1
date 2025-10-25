# operating-systems-assignment-1
CS 33211: Operating Systems
Fall 2025 Semester
Assignment 1
Author: Archie Horne 
10/20/2025


File Descriptions:
   src/consumer.cpp
        This program. when compiled and ran, will work in tandem with the producer and wait until the producer places items on the table in shared memory, where it will then take those items off the table and into itself, and then print the item to the terminal. Then, it will return to waiting for items.
   src/producer.cpp
        This program, when compiled and ran, will work in tandem with the consumer and create random numbers, print them to the terminal, and place them onto the table in shared memory until it is full. Then, it will then wait for the consumer to take them off so it can repeat and create more items. 
   makefile
        This file provides easy instructions on how to compile and execute the program.
   memorybuff.hpp 
        This file stores the struct for sharedMem, which is necessary for integrating the shared memory between producer and consumer. It also contains the initialization for the three sem_t semaphore variables.

Usage Instructions:
    This program is meant to run on a Windows operating system, but is currently not running as necessary, and may not run properly.
    The program can be run from command line (not preferred) with   
        g++ "./src/consumer.cpp" -pthread -o ./out/consumer
        g++ "./src/producer.cpp" -pthread -o ./out/producer
        start ./../out/producer.exe shmfile && start ./../out/consumer.exe shmfile

    The program can be run from the makefile (preferred) with   
        make run  
    which compiles both programs and runs them together. 

See documentation folder for more information.

Languages:
    C++
    Make

Libraries included:
    Semaphore
    MemoryAPI
    C Std Library
    I/O Stream
    UNI Std
    Pthread
    Fcntl
    Tchar
    ConI/O
    Windows 
