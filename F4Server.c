#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared_memory.h"
/// libreria per i segnali
#include <signal.h>
// libreria  per la shared memory
#include <sys/shm.h>
#include <sys/stat.h>

#define SHM_SIZE 1024

void gestore_del_segnale(int segnale) {
    printf("\nProgramma terminato.\n");
    exit(0);
}
int main(int argc, char *argv[]){
    int righe, colonne;
    int *tabellone;
    int shmid_tabellone;
    int shmid_entrata;
    char simbolo_giocatore1[2], simbolo_giocatore2[2];



    //  Creo il gestore di segnale per uscire con CTRL + C
    signal(SIGINT, gestore_del_segnale);


    /// Assegnazione input da terminale alle variabili con gestione assenza
    if(argv[1]!= NULL)
        righe = atoi(argv[1]);

    else{
        printf("Devi inserire i valori da terminale coglione \n");
        return 0;
    }
    printf("Righe : %d \n", righe);
    if(argv[2] != NULL)
        colonne = atoi(argv[2]);
    else{
        printf("Devi inserire i valori da terminale\n");
        return 0;
    }
    printf("Colonne : %d \n",colonne);
    if(argv[3] != NULL)
        strcpy(simbolo_giocatore1,argv[3]);
    else{
        printf("Devi inserire i valori da terminale\n");
        return 0;
    }
    printf("Il simbolo scelto per giocatore 1: %s \n",simbolo_giocatore1);
    if(argv[4] != NULL)
        strcpy(simbolo_giocatore2,argv[4]);
    else{
        printf("Devi inserire i valori da terminale \n");
        return 0;
    }
    printf("Il simbolo scelto per giocatore 2: %s \n",simbolo_giocatore2);

    printf("Sto aspettando i due giocatori! \n");
    ///creazione tabellone con la sua shared memory dedicata

    size_t size_tabellone = sizeof(righe*colonne*sizeof(int));
    printf("Dimensione tabellone: %ld \n",size_tabellone);
    key_t key_tabellone = 12345;
    shmid_tabellone = alloc_shared_memory(shmid_tabellone,size_tabellone,key_tabellone);
    int *ptr_1 = get_shared_memory(shmid_tabellone);
    printf("Valore shmid_tabellone : %d \n",shmid_tabellone);
    ///creazione shared memory per attivare i due client
    size_t size_entrata = sizeof(sizeof(int)*4);
    key_t key_variabile = 1234;
    shmid_entrata = alloc_shared_memory(shmid_entrata, size_entrata, key_variabile);
    int *ptr_2 =(int *) get_shared_memory(shmid_entrata);
    ptr_2[2] = size_tabellone;
    printf("Valore shmid_entrata : %d \n", shmid_entrata);
    printf("Aspettiamo il giocatore 1 che si attivi! \n");
    while(ptr_2[1] != 1){};
    printf("Giocatore 1 Arrivato! \n");
    printf("PID Giocatore 1 : %d \n",ptr_2[0]);
    printf("Aspettiamo il secondo giocatore! \n");
    while(ptr_2[1] != 2){};
    printf("Giocatore 2 arrivato! \n");
    printf("PID Giocatore 2 : %d \n",ptr_2[0]);
    printf("Ora possiamo giocare! \n");





    /// Rimozione cose

    remove_shared_memory(shmid_entrata);
    remove_shared_memory(shmid_tabellone);

}
