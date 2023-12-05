#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include "semaphore.h"
#include "shared_memory.h"
#include "errExit.h"

int main() {
    int count  = 10;
    key_t semkey = 1;
    key_t shmkey = 2;
    size_t size = sizeof(sizeof(int)*count);
    // creazione shared memory
    int shmid = alloc_shared_memory(shmid,size,shmkey);
    if(shmid == -1)
        errExit("Errore nell'allocazione della shared memory");
    int *ptr =(int *) get_shared_memory(shmid);
    ptr[0]=count;

    // Creazione semafori
    int semid = semget(semkey, 1, S_IRUSR | S_IWUSR);
    if (semid == -1)
        errExit("semget failed");
    unsigned short semInitVal[] = {1};
    union semun arg;
    arg.array = semInitVal;

    // Inizializzo il valore del semaforo dell'insieme
    if (semctl(semid, 0 , SETALL, arg) == -1)
        errExit("semctl SETALL failed");
    while(ptr[0] != 0){
        
    }

    remove_shared_memory(shmid);
    return 0;
}
