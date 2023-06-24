#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
sem_t full, empty;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Producendo l'elemento
        sleep(rand() % 3);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Inserendo l'elemento nel buffer
        buffer[item - 1] = item;
        printf("Prodotto: %d\n", item);
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Prelevando l'elemento dal buffer
        int item = buffer[item - 1];
        printf("Consumato: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // Consumando l'elemento
        sleep(rand() % 3);
    }
}

int main() {
    srand(time(NULL));

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_create(&producers[i], NULL, producer, NULL);

    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_create(&consumers[i], NULL, consumer, NULL);

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(producers[i], NULL);

    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(consumers[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
