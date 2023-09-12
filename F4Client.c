
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "shared_memory.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define  MAX 32

int  main(int argc, char *argv[]){
    pid_t pid = getpid();
    char Giocatore[MAX] ;
    int shmid_entrata;
    int shmid_tabellone;
    /// variabili per la memoria condivisa

    char array[5][4];

    strcpy(Giocatore,argv[1]);
    printf("%s \n",Giocatore);
    size_t size_entrata= sizeof(sizeof(int)*4);
    key_t key_variabile = 1234;
    shmid_entrata = alloc_shared_memory(shmid_entrata,size_entrata,key_variabile);

    printf("Valore shmid_entrata : %d \n",shmid_entrata);
    //printf("Valore PID: %d \n",pid);
    int *ptr_2 = (int *)get_shared_memory(shmid_entrata);
    size_t size_tabellone = ptr_2[2];
    ptr_2[1]++;
    if(ptr_2[0]== 0){
        ptr_2[0] = pid;
        printf("Sono il giocatore 1: %s!\n",Giocatore);
        printf("Aspettiamo il Giocatore 2!\n");

    }
    else{
        printf("Sono il giocatore 2: %s!\n",Giocatore);
        ptr_2[0] = pid;
    }

    while(ptr_2[1] != 2){}

    printf("Ora possiamo giocare!! \n");
    printf("Dimensione tabellone: %ld \n",size_tabellone);
    remove_shared_memory(shmid_entrata);
}