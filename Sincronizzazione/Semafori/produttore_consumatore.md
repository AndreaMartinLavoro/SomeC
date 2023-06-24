In questo programma, vengono utilizzati due semafori ('**empty**' e '**full**') per sincronizzare il produttore e il consumatore. Il semaforo 'empty' tiene traccia dello spazio disponibile nel buffer, mentre il semaforo '**full**' tiene traccia degli elementi presenti nel buffer.

Il produttore ciclicamente produce un elemento, inserendolo nel buffer quando c'è spazio disponibile (semaforo '**empty**'). Dopo aver inserito l'elemento, segnala che il buffer è pieno incrementando il semaforo '**full**'.

Il consumatore ciclicamente preleva un elemento dal buffer quando ci sono elementi disponibili (semaforo '**full**'). Dopo aver consumato l'elemento, segnala che il buffer ha uno spazio vuoto incrementando il semaforo '**empty**'.

Sono presenti anche un mutex ('**mutex**') per garantire l'accesso esclusivo al buffer da parte dei thread produttori e consumatori.

Nel programma, ho creato 2 produttori ('**NUM_PRODUCERS**') e 2 consumatori ('**NUM_CONSUMERS**'), ma puoi regolare questi valori secondo le tue esigenze.