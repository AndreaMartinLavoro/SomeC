/*
In questo esempio, viene definita una funzione sigint_handler 
che sarà chiamata quando il programma riceve il segnale SIGINT (generato da Ctrl+C). 
Nel gestore del segnale, viene semplicemente stampato un messaggio e il programma 
viene terminato con exit(0).
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("Ricevuto segnale SIGINT (%d)\n", signum);
    // Aggiungere qui il codice per gestire il segnale SIGINT
    exit(0);
}

int main() {
    // Impostazione del gestore per il segnale SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("Il programma è in esecuzione. Premere Ctrl+C per inviare il segnale SIGINT.\n");

    while (1) {
        // Il programma continua ad eseguire le sue operazioni qui
        sleep(1);
    }

    return 0;
}
