#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>

#define DIM 6

int flag[DIM];
int turn;
int sharedVariable = 0;

void enter_critical_section(int processId) {
    int otherProcessId = (DIM - 1) - processId;
    
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
    printf("Processo %d:    Inizio sezione critica\n", processId);
    
    sharedVariable++; // Operazione nella sezione critica

    int ttl = rand()%10;
    int ttl_bk = ttl;
    float completamento = 0;
    printf("Processo %d:    Complessita' della sezione critica pari a %d\n", processId, ttl);
    while (ttl>0)
    {
        ttl--;
        completamento = 100 - (float)ttl/ttl_bk*100;
        printf("Processo %d:        Completato per il %d/100\n", processId, (int)completamento);
    }
    
    printf("Processo %d:    Fine sezione critica\n", processId);
    leave_critical_section(processId);
    
    // Sezione non critica
    printf("Processo %d: Fine sezione non critica\n", processId);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[DIM];
    int processIds[DIM];
    
    // Inizializza le variabili condivise
    for(int i = 0; i<DIM; i++){
        flag[i] = 0;
    }

    // Inizializza i processIds
    for(int i = 0; i<DIM; i++){
        processIds[i] = i;
    }

    turn = 0;
    
    // Crea i due processi
    for(int i = 0; i<DIM; i++){
        pthread_create(&threads[i], NULL, process, (void*)&processIds[i]);
    }
    
    
    // Attendi il completamento dei processi
    for(int i = 0; i<DIM; i++){
        pthread_join(threads[i], NULL);
    }
    
    // Stampa il valore finale della variabile condivisa
    printf("Valore finale della variabile condivisa: %d\n", sharedVariable);
    
    return 0;
}