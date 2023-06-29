# Sincronizzazione
In condizioni normali, un moderno sistema operativo deve gestire più processi contemporaneamente in esecuzione
1. tali processi possono eseguire indipendentemente o essere cooperanti
2. nella situazione generale avremo processi che compiono le loro azioni inframezzandole e interessando risorse condivise
3. tali processi necessitano di
    - sincronizzazione
    - comunicazione
    - accesso a dati e informazioni condivise

**N.B.** L’accesso contemporaneo da parte di due processi a dati condivisi può essere problematico

# Concetti Essenziali
1. **Sezione Critica (SC):** Una sezione di codice che legge/scrive dati condivisi
2. **Race Condition:** Una situazione in cui l’esecuzione concorrente di una sezione critica, da parte di più processi, porta a risultati dipendenti dall’ordine in cui i processi alternano l’esecuzione delle loro istruzioni
(Ciò è potenziale fonte di inconsistenze dei dati)
3. **Mutua Esclusione:** Meccanismo con cui si evitano le race condition assicurando l’accesso esclusivo ai dati. (Un processo deve essere “autorizzato” ad entrare in una sezione critica)
4. **Deadlock (o blocco critico):** Situazione in cui dei processi sono permanentemente bloccati perchè in attesa vicendevole del rilascio di risorse
5. **Starvation:** Situazione in cui ad un processo che ha richiesto l’accesso ad una sezione critica non viene mai permesso di evolvere perchè vengono sempre servite le richieste di altri processi

# Soluzione del Problema della Sezione Critica
Consideriamo una specifica risorsa condivisa e le sezioni critiche ad essa relative presenti nei codici eseguiti da diversi processi. Una soluzione al problema della sezione critica deve garantire:
1. Mutua esclusione
2. Progresso
3. Attesa limitata

# La soluzione di Peterson

La Soluzione di Peterson è un algoritmo utilizzato per evitare la condizione di stallo (deadlock) nei sistemi operativi, in particolare quando più processi condividono risorse limitate.

### FUNZIONA:
- **turno** garantisce la mutua esclusione, elimina la possibilità del deadlock, ed evita che un processo monopolizzi la SC (infatti ogni processo concede una possibilità all’altro prima di entrare)
- l’uso dei flag evita che un processo sia “chiuso fuori” qualora l’altro non rientri in SC (perchè non vuole o perchè non può)
- permette ad un processo di entrare in SC più volte consecutive

**DIFETTO:** busy waiting

Trascurando questo difetto, abbiamo una soluzione.

**DUBBI:** come sono eseguiti gli aggiornamenti di **turno** e di **flag[i]**? con istruzioni macchina atomiche? e se ci fossero più di due processi? 

**INOLTRE:** in sistemi reali può produrre risultati incoerenti nel caso di processi multi-thread. Ad esempio a causa di ottimizzazioni introdotte dal compilatore che può riordinare le istruzioni macchina

# Barriere di memoria
In presenza di sistemi multiprocessore le modifiche alla memoria effettuate da un processore potrebbero non essere immediatamente visibili agli altri processori.
Le **memory barriers** o **memory fences** sono istruzioni che regolamentano load/store della memoria.

Esempio con due thread concorrenti:

#### Th1
```C
while (!flag)
    memory_barrier();
    y = x;
```

#### Th2
```C
x = 100;
memory_barrier();
flag = true;
```

Assicurano che Th1 legga il valore di flag prima di quello di x (impedendo per esempio che le letture vengano riordinate). Mentre la modifica di x fatta da Th2 sarà resa disponibile a Th1 prima che Th2 modifichi flag

# Istruzioni Atomiche
#### TestAndSet
È una istruzione atomica il cui effetto può essere schematizzato come segue:
```C
boolean TestAndSet (boolean *target)
{
    boolean retval = *target;
    *target = TRUE;
    return *retval;
}
```
**DIFETTO:** ancora busy waiting!!!

**DIFETTO:** non garantisce l’attesa limitata: non c’è disciplina nel selezionare chi entra (potrebbe entrare sempre lo stesso processo)
#### Swap
È una istruzione atomica il cui effetto può essere schematizzato come segue:
```C
void Swap (boolean *a, boolean *b)
{
    boolean temp = *a;
    *a = *b;
    *b = temp;
}
```
L’unico che può entrare è colui che trova lock==false 

**DIFETTO:** ancora busy waiting!!!

**DIFETTO**:** non garantisce l’attesa limitata
#### CompareAndSwap
È una istruzione atomica il cui effetto può essere schematizzato come segue:
```C
int CompareAndSwap (int *val, int test, int newval)
{
    int temp = *val;
    if (*val == test)
        *val = newval;
    return temp;
}
```
Garantisce mutua esclusione, progresso e attesa limitata 

**DIFETTO:** ancora busy waiting!!!

**N.B.** Le istruzioni appena descritte possono venir impiegate per implementare operazioni (aritmetiche, booleane, ...) su locazioni di memoria in modo che vengano **eseguite atomicamente**

# Evitare il Busy Waiting
Una soluzione ottimale dovrebbe evitare che i processi in attesa di entrare nella SC occupino la CPU inutilmente per lunghi periodi di tempo
Sarebbe meglio che un processo in attesa di entrare nella SC cambi il suo stato in **waiting**, così facendo
- non occuperebbe la CPU
- tornerebbe ready solo quando ha la possibilità di entrare nella SC
Uno strumento per raggiungere questo obiettivo è il **semaforo**

# Semafori
Un semaforo è una struttura dati costituita da
- una variabile intera S
- delle operazioni atomiche predefinite: **wait** e **signal**
    - **wait(S)** (detta anche lock(S) o P(S) o down(S)) 
    - **signal(S)** (detta anche unlock(S) o V(S) o up(S))
- eventuali operazioni per creazione e inizializzazione

Le **uniche** operazioni con cui si può accedere ad un semaforo S sono
quindi **wait(S)** e **signal(S)**
A seconda dei valori ammessi per S si distingue tra: 
- **semaforo binario** se il valore può essere solo 0 o 1
    - **semaforo di sincronizzazione** se inizializzato a 0
    - **mutex** se inizializzato a 1 (MUTUA ESCLUSIONE)
- **semaforo generico**, se il valore può essere un intero
# Monitor
In informatica, un monitor è una struttura di sincronizzazione utilizzata per controllare l'accesso concorrente a risorse condivise. 
Fornisce un meccanismo per garantire che solo un thread alla volta possa eseguire un blocco di codice all'interno del monitor, evitando così le condizioni di race e l'accesso simultaneo non controllato alle risorse.
Per garantire la mutua esclusione, i processi che invocano un monitor sono inseriti in una coda di ingresso. Si può evitare la starvation con opportuno scheduling della coda

**N.B.** le chiamate nidificate di monitor devono essere vietate.

Un monitor **NON** può chiamare altri monitor monitor!!!

# POSIX Thread
I **POSIX Threads**, solitamente denominati pthreads, sono un modello di esecuzione che esiste indipendentemente da un linguaggio di programmazione, nonché un modello di esecuzione parallelo. 
Consente a un programma di controllare più flussi di lavoro diversi che si sovrappongono nel tempo. 
Ogni flusso di lavoro viene definito thread e la creazione e il controllo di questi flussi si ottiene effettuando chiamate all'API dei thread POSIX. POSIX Threads è un'API 

I pthread, che sta per "POSIX threads", sono un'interfaccia di programmazione per la gestione dei thread in sistemi operativi POSIX-compatibili. 
Sono un'implementazione di thread a livello di libreria, il che significa che non sono né specificamente "ult" né "klt".

# Nota
Nei monitor e nei semafori i principali esempi di utilizzo sono:
1. Problema dei cinque filosofi
2. Problema dei produttori e consumatori
3. Problema dei lettori e scrittori