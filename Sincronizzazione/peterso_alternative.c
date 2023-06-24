/* ============================================================================
*
* La Soluzione di Peterson è un algoritmo utilizzato per evitare la condizione 
* di stallo (deadlock) nei sistemi operativi, in particolare quando più
* processi condividono risorse limitate.
*
============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
//#include <sched.h>                                // sched_getcpu();



#define DEBUG 0                                     // Abilitare se si vuole vedere il progresso della sezione critica
#define DIM 6



int flag[DIM];
int turn;
int sharedVariable = 0;



void enter_critical_section(int processId) {
    int otherProcessId = (processId - 1) % DIM;     // Prendo l'ID del processo precedente
    
    // Imposta il flag corrente su true
    flag[processId] = 1;
    
    if(flag[otherProcessId] == 1) printf("Processo %d >     Aspetto il Processo: %d (turno: %d)\n", processId, otherProcessId, turn);
    
    // Aspetta che l'altro processo abbia finito
    while (flag[otherProcessId] == 1 && turn != processId);
}



void leave_critical_section(int processId) {
    // Resetta il flag del processo corrente a false
    flag[processId] = 0;
    turn ++;
}



void* process(void* processIdPtr) {
    int processId = *((int*)processIdPtr);
    //int cpu = sched_getcpu();                     // Stampo su che CPU viene eseguito il processo


    //______________ Sezione non critica ______________________________________
    //printf("Processo %d > instanziato sulla CPU %d", cpu);
    printf("Processo %d > Inizio sezione NON critica\n", processId);
    int ttl_nc = rand() % 10000;
    printf("Processo %d >   TTL_NC: %d\n", processId, ttl_nc);
    for(int i = 0; i < ttl_nc; i++);


    //______________  Sezione critica _________________________________________
    enter_critical_section(processId);
    printf("Processo %d >     Inizio sezione critica\n", processId);
    
    sharedVariable++; // Operazione nella sezione critica

    int ttl_sc = rand() % 1000;
    printf("Processo %d >     TTL_SC: %d\n", processId, ttl_sc);
    for(int i = 0; i < ttl_sc; i++) {
        if(DEBUG == 1) {
            float aux = ((float) i / ttl_sc) * 100.0;
            printf("Processo %d >       Completamento = %f/100\n", processId, aux);
        }
    }
    printf("Processo %d >     Fine sezione critica\n", processId);
    leave_critical_section(processId);


    //______________  Sezione non critica  ____________________________________
    printf("Processo %d >   Fine sezione NON critica\n", processId);
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
    for(int i = 0; i<DIM; i++) {
        processIds[i] = i;
    }

    turn = 0;
    
    // Crea i due processi
    for(int i = 0; i < DIM; i++) {
        pthread_create(&threads[i], NULL, process, (void*)&processIds[i]);
    }
    
    
    // Attendi il completamento dei processi
    for(int i = 0; i < DIM; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Stampa il valore finale della variabile condivisa
    printf("\nValore finale della variabile condivisa: %d\n", sharedVariable);
    
    return(EXIT_SUCCESS);
}