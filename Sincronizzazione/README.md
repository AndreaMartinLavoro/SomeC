# La soluzione di Peterson

Un algoritmo di sincronizzazione utilizzato per gestire l'accesso a risorse condivise da parte di processi concorrenti in un ambiente di programmazione. L'esempio si basa sull'utilizzo di due processi (P0 e P1) e utilizza le variabili flag e turn per coordinare l'accesso alla sezione critica.

In questo esempio, ci sono due processi (P0 e P1) che accedono alla sezione critica, rappresentata dall'incremento della variabile condivisa **sharedVariable**. L'algoritmo di Peterson viene utilizzato per sincronizzare l'accesso a questa sezione critica, garantendo che solo un processo possa accedervi alla volta.

Si prega di notare che questo esempio utilizza la libreria **pthread** per la gestione dei thread in C. Assicurati di compilare il codice utilizzando l'opzione **-pthread** per includere le librerie di supporto.

### FUNZIONA:
- **turno** garantisce la mutua esclusione, elimina la possibilità del deadlock, ed evita che un processo monopolizzi la SC (infatti ogni processo concede una possibilità all’altro prima di entrare)
- l’uso dei flag evita che un processo sia “chiuso fuori” qualora l’altro non rientri in SC (perchè non vuole o perchè non può)
- permette ad un processo di entrare in SC più volte consecutive

**DIFETTO:** busy waiting

Trascurando questo difetto, abbiamo una soluzione.

**DUBBI:** come sono eseguiti gli aggiornamenti di **turno** e di **flag[i]**? con istruzioni macchina atomiche? e se ci fossero più di due processi? 

**INOLTRE:** in sistemi reali può produrre risultati incoerenti nel caso di processi multi-thread. Ad esempio a causa di ottimizzazioni introdotte dal compilatore che può riordinare le istruzioni macchina