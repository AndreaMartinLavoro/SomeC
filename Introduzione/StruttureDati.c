#include<stdio.h>
#include<stdlib.h>

int main(){
    // Tipi enumerati
    enum nometipo { uno=1, due=2, tre=3 };    // Dichiarazione di enum
    enum nometipo nomevar;                   // Dichiarazione della variabile

    // La variabile nomevar potrà assumere come valore uno tra gli identificatori elencati nella dichiarazione di tipo.
    nomevar = due;

    struct persona persona1;
    struct persona persona2 = { 30, "Mario" };
    struct persona amici[30];

    // L’accesso ai valori dei campi si attua tramite la dot-notation:
    persona1.eta = 25;
    strcpy(persona1.nome, "Elena");

    printf("Eta‘:%d nome:%s\n", persona1.eta, persona1.nome);
    printf("Eta‘:%d nome:%s\n", persona2.eta, persona2.nome);

    amici[4].eta = 12;
    amici[4].nome = "Lily";
    amici[7] = persona1;

    printf("Eta‘:%d nome:%s\n", amici[4].eta, amici[4].nome);
    printf("Eta‘:%d nome:%s\n", amici[7].eta, amici[7].nome);


    // Un tipico uso di union è come campo in un struct assieme a un altro campo che indica l’accesso corretto alla union.
    enum tipo_di_numero { INTERO, REALE, REALEDOPPIO } ;

    struct numero {
		enum tipo_di_numero tipo;

		// union anonima: non c'e' il nome della union
		union { 
				int intero;
				double reale;
				long double realelong;
		};
    };

    struct numero x;

    if (x.tipo == INTERO) printf("intero:%d\n", x.intero);
    else if (x.tipo == REALE) printf("Reale:%d\n", x.reale);
    else if (x.tipo == REALEDOPPIO)printf("Reale long:%d\n", x.realelong);

    // typedef
    typedef int lunghezza;        // lunghezza e‘ un nuovo tipo
    typedef char parola10[11];    // parola10 e‘ tipo di stringa di max 10 char

    typedef struct tipopersona {
		int eta;
		char nome[20];
    } tipopersona;

    // In virtù di tali dichiarazioni di tipo, è possibile scrivere le seguenti dichiarazioni di variabili:
    lunghezza len;
    lunghezza max_l;

    parola10 verbo = "bere";

    tipopersona persona2 = { 30, "Mario" };

    tipopersona amici[30];
    
    return (EXIT_SUCCESS);
}

// Struct
struct persona {
		int eta;
        char nome[20];
};

//Union
union numero {
		int intero;              // 4 byte
		double reale;            // 8 byte
		long double realelong;   // 16 byte
};