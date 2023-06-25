/*
Questo esempio dimostra l'utilizzo delle pipe per la comunicazione tra processi in C. Il processo figlio scrive un numero nella pipe e il processo genitore lo legge. Naturalmente, nelle applicazioni reali, si possono scambiare dati più complessi attraverso la pipe.
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Processo figlio

        // Chiudiamo l'estremità di lettura della pipe nel processo figlio
        close(pipefd[0]);

        // Scriviamo nella pipe dal processo figlio
        int number = 42;
        if (write(pipefd[1], &number, sizeof(number)) == -1) {
            perror("write");
            return 1;
        }

        // Chiudiamo l'estremità di scrittura della pipe nel processo figlio
        close(pipefd[1]);

        printf("Il processo figlio ha scritto il numero nella pipe.\n");
    } else {
        // Processo genitore

        // Chiudiamo l'estremità di scrittura della pipe nel processo genitore
        close(pipefd[1]);

        // Leggiamo dalla pipe nel processo genitore
        int received_number;
        if (read(pipefd[0], &received_number, sizeof(received_number)) == -1) {
            perror("read");
            return 1;
        }

        // Chiudiamo l'estremità di lettura della pipe nel processo genitore
        close(pipefd[0]);

        printf("Il processo genitore ha letto il numero %d dalla pipe.\n", received_number);
    }

    return 0;
}
