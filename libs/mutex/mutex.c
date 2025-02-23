#include "mutex.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int addr_is_valid(uintptr_t address)
{
    unsigned char vec;
    return mincore((void*)address, 1, &vec);
}


mutex_t* mutex_init(char* address)
{

    char path[100];
    strcpy(path, "/tmp/");
    strcat(path, address);
    printf("%s\n", path);

    int fd = open(path, O_RDWR|O_CREAT, 0666);
    
    if(fd == -1) {
      perror("open failed\n");
      exit(EXIT_FAILURE);
    }

    if(ftruncate(fd, sizeof(mutex_t)) == -1) {
      perror("ftrucnate error\n");
      exit(EXIT_FAILURE);
    }

    mutex_t* mutex_var = (mutex_t*)mmap(NULL,
    sizeof(mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if(mutex_var == MAP_FAILED) {
        perror("Error creating mutex\n");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return mutex_var;
}

mutex_t* fetch_mutex(char* address)
{
  char path[100];
  strcpy(path, "/tmp/");
  strcat(path, address);

  int fd = open(path, O_RDWR);

  if(fd == -1) {
    perror("open failed\n");
    exit(EXIT_FAILURE);
  }

  mutex_t* mutex_var = (mutex_t*)mmap(NULL, sizeof(mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if(mutex_var == MAP_FAILED) {
    perror("error creating mutex\n");
    exit(EXIT_FAILURE);
  }

  return mutex_var;
}

void mutex_insert(mutex_t* mutex, void* value)
{
    mutex->data = value;
}

void* mutex_get(mutex_t* mutex)
{
    mutex->lock = 0;
    return mutex->data;
}

void mutex_set_lock(mutex_t* mutex)
{
    mutex->lock = 1;
}

void mutex_unset_lock(mutex_t* mutex)
{
    while(mutex->lock == 1);
}

void mutex_free(mutex_t* mutex)
{
    munmap(mutex, sizeof(mutex_t));
}
