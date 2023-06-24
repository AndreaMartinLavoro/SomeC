/*
I POSIX Threads, solitamente denominati pthreads, 
sono un modello di esecuzione che esiste indipendentemente da un linguaggio di programmazione, 
nonché un modello di esecuzione parallelo. 
Consente a un programma di controllare più flussi di lavoro diversi che si sovrappongono nel tempo. 
Ogni flusso di lavoro viene definito thread e la creazione e il controllo di questi flussi si ottiene 
effettuando chiamate all'API dei thread POSIX. POSIX Threads è un'API 

I pthread, che sta per "POSIX threads", 
sono un'interfaccia di programmazione per la gestione dei thread in sistemi operativi POSIX-compatibili. 
Sono un'implementazione di thread a livello di libreria, 
il che significa che non sono né specificamente "ult" né "klt".

In informatica, un monitor è una struttura di sincronizzazione utilizzata 
per controllare l'accesso concorrente a risorse condivise. 
Fornisce un meccanismo per garantire che solo un thread alla volta 
possa eseguire un blocco di codice all'interno del monitor, 
evitando così le condizioni di race e l'accesso simultaneo non controllato alle risorse.
*/

#include <stdio.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
} Monitor;

Monitor monitor;
int sharedResource = 0;

//per inizializzare il monitor
void initMonitor(Monitor* monitor) {
    pthread_mutex_init(&(monitor->mutex), NULL);
    pthread_cond_init(&(monitor->cond), NULL);
    monitor->count = 0;
}

//chiamata all'inizio di una sezione critica per acquisire l'accesso al monitor
void enterMonitor(Monitor* monitor) {
    pthread_mutex_lock(&(monitor->mutex));
    monitor->count++;
    pthread_mutex_unlock(&(monitor->mutex));
}

//viene chiamata alla fine per rilasciarlo
void exitMonitor(Monitor* monitor) {
    pthread_mutex_lock(&(monitor->mutex));
    monitor->count--;
    if (monitor->count == 0) {
        pthread_cond_signal(&(monitor->cond));
    }
    pthread_mutex_unlock(&(monitor->mutex));
}

//viene utilizzata quando un thread desidera attendere una certa condizione all'interno del monitor
void waitForCondition(Monitor* monitor) {
    pthread_mutex_lock(&(monitor->mutex));
    while (monitor->count > 0) {
        pthread_cond_wait(&(monitor->cond), &(monitor->mutex));
    }
    pthread_mutex_unlock(&(monitor->mutex));
}

void* threadFunction(void* arg) {
    int threadId = *(int*)arg;
    
    enterMonitor(&monitor); //thread acquisisce l'accesso al monitor
    
    // Sezione critica
    printf("Thread %d: Sto accedendo alla risorsa condivisa.\n", threadId);
    sharedResource++;
    printf("Thread %d: Valore della risorsa condivisa: %d\n", threadId, sharedResource);
    
    exitMonitor(&monitor); //thread rilascia il monitor
    
    return NULL;
}


//eseguendo il programma, si noterà che i due thread accedono in modo alternato alla risorsa condivisa, 
//garantendo l'accesso esclusivo.
int main() {
    initMonitor(&monitor); //inizializzo il monitor

    pthread_t thread1, thread2;
    int threadId1 = 1;
    int threadId2 = 2;

    //creo un nuovo thread
    pthread_create(
        &thread1,   //puntatore a una variabile di tipo pthread_t che rappresenta il thread appena creato
        NULL,   //puntatore a un oggetto di tipo pthread_attr_t che specifica gli attributi del thread
        threadFunction, //puntatore alla funzione che il nuovo thread dovrà eseguire una volta creato
        &threadId1  //puntatore al parametro che viene passato alla funzione
    );

    pthread_create(&thread2, NULL, threadFunction, &threadId2);
    
    //aspetta che un thread termini la sua esecuzione
    pthread_join(
        thread1,    //thread che vogliamo attendere
        NULL    //puntatore a un puntatore di tipo void che può essere utilizzato per recuperare il valore di ritorno del thread
    );

    pthread_join(thread2, NULL);
    
    return 0;
}