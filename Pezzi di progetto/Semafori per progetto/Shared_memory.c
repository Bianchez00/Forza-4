
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include "errExit.h"
#include "shared_memory.h"



int alloc_shared_memory(int shmid,size_t size,key_t key) {
    // get, or create, a shared memory segment
    shmid = shmget(key, size, IPC_CREAT| S_IRUSR | S_IWUSR);
    if (shmid == -1)
        errExit("shmget failed");

    return shmid;
}

void *get_shared_memory(int shmid) {
    // attach the shared memory
    void *ptr_sh = shmat(shmid, NULL,0);
    if (ptr_sh == (void *)-1)
        errExit("shmat failed");

    return ptr_sh;
}

void free_shared_memory(void * ptr) {
    // detach the shared memory segments
    if(shmdt(ptr) == -1){
        errExit("Errore nello sgancio della shared memory del tabellone");
    }
}

void remove_shared_memory(int shmid) {
    if(shmctl(shmid, IPC_RMID,NULL) == -1)
        errExit("Errore nella rimozione della shared memory ");

}