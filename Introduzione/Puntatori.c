#include<stdio.h>
#include<stdlib.h>

int main(){
    int intero = 20;    // ptr_intero ha tipo int*
    int *ptr_intero;    // Cioe' "puntatore ad intero"
    int *ptrbis;        // Un altro puntatore ad intero

    // L’operatore & permette di accedere all’indirizzo di una variabile:
    ptr_intero = &intero;

    // Tramite l’operatore di deferenziazione * si può invece denotare “l’oggetto puntato”, come in:
    intero = *ptr_intero;    // Assegna il valore puntato
    *ptr_intero = intero;    // Scrive all’indirizzo

    // Per tutti i tipi T esiste il corrispondente tipo T*, “puntatote a T”:
    char *ptr_c;
    long double *ptr_doppiolungo;
    tipopersona *puntaPersona;

    // Anche per gli stessi tipi puntatore:
    char **ppc;    // puntatore a puntatore a char
    long **ppl;    // puntatore a puntatore a long

    // La costante predefinita NULL indica il puntatore nullo tale valore può essere usato con qualsiasi tipo puntatore:
    float **punt1 = NULL;
    puntaPersona = NULL;

    // Questo esempio illustra la possibilità di causare side effect:
    int x=1, y=2, z[10];
    int *ip;                   // ip e‘ puntatore a int,
    z[0]=5;                    // ovvero l’oggetto *ip e‘ di tipo int
    ip = &x;                   // ora ip punta a x, la stessa locazione di memoria viene acceduta tramite x e ip
    y = *ip;                   // ora y vale 1
    *ip = 0;                   // ora x vale 0
    ip = &z[0];                // ora ip punta a z[0]
    
    // TODO - Puntatori: precedenze
    
    return (EXIT_SUCCESS);
}