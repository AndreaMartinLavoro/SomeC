#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DIM 10
#define MAX_TODO 10

// Definizione della struttura semaforo
typedef struct {
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Semaphore;

// Inizializzazione del semaforo
void semaphore_init(Semaphore* sem, int initial_count) {
    sem->count = initial_count;
    pthread_mutex_init(&(sem->mutex), NULL);
    pthread_cond_init(&(sem->cond), NULL);
}

// Wait (acquisizione) del semaforo
void semaphore_wait(Semaphore* sem) {
    pthread_mutex_lock(&(sem->mutex));
    while (sem->count <= 0) {
        pthread_cond_wait(&(sem->cond), &(sem->mutex));
    }
    sem->count--;
    pthread_mutex_unlock(&(sem->mutex));
}

// Signal (rilascio) del semaforo
void semaphore_signal(Semaphore* sem) {
    pthread_mutex_lock(&(sem->mutex));
    sem->count++;
    pthread_cond_signal(&(sem->cond));
    pthread_mutex_unlock(&(sem->mutex));
}

// Esempio di utilizzo dei semafori
Semaphore mutex;

void* process(void* processIdPtr) {
    int processId = *((int*)processIdPtr);
    
    // Sezione non critica
    printf("Processo %d: Inizio sezione non critica\n", processId);
    
    // Wait del semaforo
    semaphore_wait(&mutex);
    
    printf("Processo %d:    Inizio sezione critica\n", processId);

    int ttl = rand()%MAX_TODO;
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
    
    // Signal del semaforo
    semaphore_signal(&mutex);
    
    // Sezione non critica
    printf("Processo %d: Fine sezione non critica\n", processId);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[DIM];
    int processIds[DIM];
    
    // Inizializzazione del semaforo con count iniziale 1 (MUTUA ESCLUSIONE) 
    semaphore_init(&mutex, 1);

    // Inizializza i processIds
    for(int i = 0; i<DIM; i++){
        processIds[i] = i;
    }
    
    // Creazione dei thread
    for (int i = 0; i < DIM; i++) {
        pthread_create(&threads[i], NULL, process, (void*)&processIds[i]);
    }
    
    // Join dei thread
    for (int i = 0; i < DIM; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Distruzione del semaforo
    pthread_mutex_destroy(&(mutex.mutex));
    pthread_cond_destroy(&(mutex.cond));
    
    return 0;
}