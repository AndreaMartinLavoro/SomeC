#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// definizione di una macro:
#define N 2000

int main() {
    HelloWorld();
    SizeOf();
    CalcolaAssegna();
    SomeBool();
    OperazioniBitToBit();
    printf("Valore restituito:%d\n", mia_funzione(3, 7, 9));
    printf("Valore restituito:%d\n", staticFun(9));

    return (EXIT_SUCCESS);
    /* 
    *   La costante EXIT_SUCCESS (in linux ha valore 0) 
    *   è definita nello header stdlib.h (così come EXIT_FAILURE) 
    */
}

/* Stampa "Ciao mondo" */
void HelloWorld(){
    printf("Ciao mondo\n");
    // Ok ora sai programmare in C :-)
}

/* Esempi con variabile e sizeof */
void SizeOf(){
    char c; // dichiarazione di una variabile char,
    short s = 11; // una variabile short inizializzata
    int i = N; // inizializzata usando la macro N

    printf("size of char:%lu\n", sizeof(c));
    printf("size of short:%lu\n", sizeof(s));
    printf("size of int:%lu\n", sizeof(i));

    // l’argomento di sizeof() puo‘ essere il tipo:
    printf("size of long:%lu\n", sizeof(long));
    printf("size of float:%lu\n", sizeof(float));
    printf("size of double:%lu\n", sizeof(double));
    printf("size of long double:%lu\n", sizeof(long double));
}

/* Esempi con Calcoli e Assegnazioni */
void CalcolaAssegna(){
    char c; // dichiarazione di una variabile char,
    short s = 11;  // una variabile short inizializzata
    int i = N;  // inizializzata usando la macro N
    float f = 10.0;  // inizializzata a 0.0 float
    
    f = f + 25.0 / N;
    c = 'K'; // inizializzo c al carattere ’K’
    
    printf("Il valore di s: %d \n", s);
    printf("Il valore di i: %d e quello di N: %d\n", i, N);
    printf("Il valore di f: %f \nIl valore di c: %c \n", f, c);
}

/* Esempi con i bool */
void SomeBool(){
    bool controllo = true;

    if(4+7) {
        printf("vero\n");
    }  
    else{
        // solo se == 0
        printf("falso\n");
    }

    if(controllo){
        printf("Il controllo funziona!\n");
    }
}

/* Esempi di Operzioni bit a bit */
void OperazioniBitToBit(){
    unsigned char c = ’z’; // sizeof(unsigned char) e‘ 1 byte
    unsigned char d;
    
    d=c;
    c = (c & ~(1<<4)); /* (1<<4) e‘ il binario 00010000,
                            ~ complementa, quindi l’assegnamento
                            azzera il quarto bit di c */

    printf("Vecchio valore:%c Nuovo valore:%c\n", d, c);
    printf("Vecchio valore:%d Nuovo valore:%d\n", d, c);
}

/* Esempio di funzione */
int mia_funzione(int x, int val, float arg_reale){
    int varlocale = val * x;
    if(arg_reale > 0){
        return(varlocale);
    } else {
        return(x + 2 * val);
    }
}

/* Esempio con variabili locali statiche */
int staticFun(int arg) {
       static int varlocale = 0;
       varlocale = varlocale + arg;
       return(arg);
}