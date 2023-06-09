#include <stdio.h>
#include <pthread.h>

int flag[2];
int turn;
int sharedVariable = 0;

void enter_critical_section(int processId) {
    int otherProcessId = 1 - processId;
    
    // Imposta il flag corrente su true e imposta il turno all'altro processo
    flag[processId] = 1;
    turn = otherProcessId;
    
    // Aspetta che l'altro processo abbia finito
    while (flag[otherProcessId] == 1 && turn == otherProcessId) {
        // Attendi
    }
}

void leave_critical_section(int processId) {
    // Resetta il flag del processo corrente a false
    flag[processId] = 0;
}

void* process(void* processIdPtr) {
    int processId = *((int*)processIdPtr);
    
    // Sezione non critica
    printf("Processo %d: Inizio sezione non critica\n", processId);
    
    // Sezione critica
    enter_critical_section(processId);
    printf("Processo %d: Inizio sezione critica\n", processId);
    
    sharedVariable++; // Operazione nella sezione critica
    
    printf("Processo %d: Fine sezione critica\n", processId);
    leave_critical_section(processId);
    
    // Sezione non critica
    printf("Processo %d: Fine sezione non critica\n", processId);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int processIds[2] = {0, 1};
    
    // Inizializza le variabili condivise
    flag[0] = 0;
    flag[1] = 0;
    turn = 0;
    
    // Crea i due processi
    pthread_create(&threads[0], NULL, process, (void*)&processIds[0]);
    pthread_create(&threads[1], NULL, process, (void*)&processIds[1]);
    
    // Attendi il completamento dei processi
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    // Stampa il valore finale della variabile condivisa
    printf("Valore finale della variabile condivisa: %d\n", sharedVariable);
    
    return 0;
}
