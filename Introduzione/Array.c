#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
    int vet[6] = { 0, 3, -5, 6, 4, 6 };

    // L’accesso ad una delle componenti avviene indicandone l’indice:
    vet[4] = 0;
    vet[2] = 3 * vet[4];

    // Si noti che il compilatore gcc (normalmente) non effettua nessun controllo sui valori degli indici utilizzati nell’accesso.
    printf("vet[%d]:%d\n", 9, vet[9]);

    // In C le stringhe sono array di char terminati dal carattere ‘\0’ (“terminatore”).
    char miastringa[10] = "libro";

    // L’header file string.h definisce molte funzioni per manipolare le stringhe, cioè array di char terminati da ’\0’.
    strcmp();    // Compara 2 stringhe
    strcpy();    // Copia una stringa in un altra
    strlen();    // Restituisce la lunghezza di una stringa (escluso '\0')
    strcat();    // Concatena 2 stringhe
    
    return (EXIT_SUCCESS);
}