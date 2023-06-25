# Pipe
Interprocess communication
Le pipe costituiscono un meccanismo semplice di comunicazione
- Generalizzano la nozione di file: due (i più) processi potrebbero utilizzare un file aperto in scrittura/lettura per scrivere/leggere.
Tale soluzione presenta inefficienze.
- Una **pipe** realizza un canale di comunicazione unidirezionale: due “estremi” uno di scrittura ed uno di lettura
**N.B.** sono possibili due principali operazioni sulla pipe: **write()** e **read()** (oltre alla **close()**)

Il prototipo è il seguente:
```C
#include <unistd.h>

int pipe(int pipefd[2]);
```
Dove **pipefd** è un array di due interi che conterrà i due descrittori di file identificanti la pipe.

Il primo (**pipefd[0]**) è utilizzabile per leggere dalla pipe, mentre il second (**pipefd[1]**) per scrivervi.

L’utilità di una pipe diventa evidente quando viene impiegata in congiunzione alla chiamata di sistema **fork()**: come per i file, anche i due descrittori associati ad una pipe vengono ereditati dal processo figlio.

# I Segnali
- I segnali in Unix/Linux sono un meccanismo semplice per inviare degli interrupt software ai processi
- Realizzano una forma di comunicazione essenzialmente asincrona
- Esistono diversi segnali connessi a particolari eventi che si possono verificare nel sistema

**SPEDIZIONE:** un processo (utente o, più solitamente, di sistema) può inviare un segnale a un processo (o a un gruppo di processi)

**RICEZIONE:** i segnali possono essere ricevuti e poi gestiti o ignorati, oppure possono venir bloccati, in tal caso restano pendenti
la gestione di un segnale può essere decisa dal processo stesso, tramite l’“installazione di uno handler del segnale”

Invio di un segnale da programma
```C
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
```
dove pid può essere
- n il segnale viene inviato al processo con PID=n
- 0 il segnale viene inviato a tutti i processi del gruppo del chiamante
- -1 il segnale viene inviato a tutti i processi con PID>1 (limitatamente ai permessi posseduti dal chiamante) tranne il chiamante stesso
- -n (con n > 1) il segnale viene inviato a tutti i processi del gruppo n

# Socket
I socket sono un'interfaccia di programmazione (API) che permette la comunicazione tra processi in una rete o tra processi locali sullo stesso sistema operativo. Essi forniscono un meccanismo standardizzato per l'invio e la ricezione di dati tra applicazioni.

Un socket può essere immaginato come un punto di accesso attraverso il quale le applicazioni possono scambiare dati. Esso rappresenta un canale di comunicazione bidirezionale tra due processi, dove un processo può inviare dati attraverso il socket e l'altro processo può riceverli.

Esistono due tipi principali di socket:

- **Socket di dominio** degli indirizzi Internet (AF_INET): Questi socket sono utilizzati per la comunicazione su reti IP. Gli indirizzi IP (ad esempio IPv4 o IPv6) e i numeri di porta vengono utilizzati per identificare i punti terminali della connessione.

- **Socket di dominio** Unix (AF_UNIX o AF_LOCAL): Questi socket sono utilizzati per la comunicazione locale all'interno di un sistema operativo basato su Unix. Invece di utilizzare indirizzi IP, utilizzano percorsi di file nel file system per identificare i punti terminali della connessione.

La comunicazione attraverso i socket avviene mediante la creazione, l'associazione, l'ascolto e l'accettazione di connessioni. Un processo può creare un socket utilizzando la funzione **socket()**, associarlo a un indirizzo utilizzando la funzione **bind()**, metterlo in ascolto utilizzando la funzione listen() e accettare le connessioni in arrivo utilizzando la funzione **accept()**.

Una volta che i socket sono connessi, i processi possono utilizzare le funzioni **send()** e **recv()** per inviare e ricevere dati attraverso il socket. Esistono anche altre funzioni per la gestione dei socket, come la configurazione delle opzioni di socket, la chiusura dei socket e la gestione degli errori.

I socket sono ampiamente utilizzati per lo sviluppo di applicazioni di rete, come server web, client di posta elettronica, chat, giochi online e molte altre applicazioni che richiedono la comunicazione tra processi su una rete o all'interno di un sistema operativo.