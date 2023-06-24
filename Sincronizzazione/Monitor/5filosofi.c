#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Numero di filosofi

typedef enum { THINKING, HUNGRY, EATING } PhilosopherState;

typedef struct {
    PhilosopherState states[N];
    pthread_mutex_t mutex;
    pthread_cond_t cond[N];
} DiningPhilosophers;

void initPhilosophers(DiningPhilosophers *diningPhilosophers) {
    int i;
    for (i = 0; i < N; i++) {
        diningPhilosophers->states[i] = THINKING;
    }
    pthread_mutex_init(&diningPhilosophers->mutex, NULL);
    for (i = 0; i < N; i++) {
        pthread_cond_init(&diningPhilosophers->cond[i], NULL);
    }
}

void pickUpChopsticks(DiningPhilosophers *diningPhilosophers, int philosopher) {
    pthread_mutex_lock(&diningPhilosophers->mutex);
    diningPhilosophers->states[philosopher] = HUNGRY;
    test(philosopher, diningPhilosophers);
    if (diningPhilosophers->states[philosopher] != EATING) {
        pthread_cond_wait(&diningPhilosophers->cond[philosopher], &diningPhilosophers->mutex);
    }
    pthread_mutex_unlock(&diningPhilosophers->mutex);
}

void putDownChopsticks(DiningPhilosophers *diningPhilosophers, int philosopher) {
    pthread_mutex_lock(&diningPhilosophers->mutex);
    diningPhilosophers->states[philosopher] = THINKING;
    test((philosopher + 4) % N, diningPhilosophers);
    test((philosopher + 1) % N, diningPhilosophers);
    pthread_mutex_unlock(&diningPhilosophers->mutex);
}

void test(int philosopher, DiningPhilosophers *diningPhilosophers) {
    if (diningPhilosophers->states[philosopher] == HUNGRY &&
        diningPhilosophers->states[(philosopher + 4) % N] != EATING &&
        diningPhilosophers->states[(philosopher + 1) % N] != EATING) {
        diningPhilosophers->states[philosopher] = EATING;
        pthread_cond_signal(&diningPhilosophers->cond[philosopher]);
    }
}

void *philosopherThread(void *arg) {
    DiningPhilosophers *diningPhilosophers = (DiningPhilosophers *)arg;
    int philosopher = *((int *)arg);
    
    while (1) {
        // Filosofo pensa
        printf("Filosofo %d sta pensando.\n", philosopher);
        sleep(rand() % 3);
        
        // Filosofo affamato
        printf("Filosofo %d ha fame e vuole mangiare.\n", philosopher);
        
        // Prende le bacchette
        pickUpChopsticks(diningPhilosophers, philosopher);
        
        // Filosofo mangia
        printf("Filosofo %d sta mangiando.\n", philosopher);
        sleep(rand() % 3);
        
        // Posiziona le bacchette
        putDownChopsticks(diningPhilosophers, philosopher);
    }
    
    return NULL;
}

int main() {
    srand(time(NULL));
    
    DiningPhilosophers diningPhilosophers;
    initPhilosophers(&diningPhilosophers);
    
    pthread_t philosophers[N];
    int i;
    for (i = 0; i < N; i++) {
        int *philosopher = malloc(sizeof(int));
        *philosopher = i;
        pthread_create(&philosophers[i], NULL, philosopherThread, philosopher);
    }
    
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    return 0;
}
