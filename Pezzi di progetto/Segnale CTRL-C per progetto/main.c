#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Flag per contare il numero di segnali CTRL-C ricevuti
int ctrl_c_count = 0;

// Funzione di gestione del segnale CTRL-C
void control_c_handler(int signum) {
    if (ctrl_c_count == 0) {
        printf("Ricevuto segnale CTRL-C. Premere nuovamente per terminare.\n");
        ctrl_c_count++;
    } else {
        printf("Terminazione del programma.\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, control_c_handler);


    while (1) {
        printf("Server in attesa...\n");
        sleep(1);
    }

    return 0;
}

