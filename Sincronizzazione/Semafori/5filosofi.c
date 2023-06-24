#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILOSOFI 5
#define PENSIERI_MAX 5

// Definizione della struttura semaforo
typedef struct {
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Semaphore;

typedef struct {
    int id;
    Semaphore* forchette[NUM_FILOSOFI];
} Filosofo;

Semaphore mutex;
Filosofo filosofi[NUM_FILOSOFI];

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

void pensa(int id) {
    printf("Filosofo %d: Sta pensando...\n", id);
    sleep(rand() % PENSIERI_MAX + 1);
}

void mangia(int id) {
    printf("Filosofo %d: Vuole mangiare...\n", id);
    
    semaphore_wait(&mutex);
    semaphore_wait(filosofi[id].forchette[id]);
    semaphore_wait(filosofi[id].forchette[(id + 1) % NUM_FILOSOFI]);
    semaphore_signal(&mutex);
    
    printf("Filosofo %d: Ha iniziato a mangiare!\n", id);
    sleep(rand() % PENSIERI_MAX + 1);
    printf("Filosofo %d: Ha finito di mangiare!\n", id);
    
    semaphore_signal(filosofi[id].forchette[id]);
    semaphore_signal(filosofi[id].forchette[(id + 1) % NUM_FILOSOFI]);
}

void* filosofo_thread(void* filosofo) {
    Filosofo* fil = (Filosofo*)filosofo;
    
    while (1) {
        pensa(fil->id);
        mangia(fil->id);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t filosofi_threads[NUM_FILOSOFI];
    
    // Inizializzazione dei semafori per le forchette
    for (int i = 0; i < NUM_FILOSOFI; i++) {
        filosofi[i].id = i;
        filosofi[i].forchette[i] = malloc(sizeof(Semaphore));
        semaphore_init(filosofi[i].forchette[i], 1);
    }
    
    // Inizializzazione del semaforo mutex
    semaphore_init(&mutex, NUM_FILOSOFI - 1);
    
    // Creazione dei thread dei filosofi
    for (int i = 0; i < NUM_FILOSOFI; i++) {
        pthread_create(&filosofi_threads[i], NULL, filosofo_thread, (void*)&filosofi[i]);
    }
    
    // Join dei thread dei filosofi
    for (int i = 0; i < NUM_FILOSOFI; i++) {
        pthread_join(filosofi_threads[i], NULL);
    }
    
    return 0;
}
