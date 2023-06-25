/*
In questo esempio, viene creato un semplice server TCP che accetta connessioni dai client.
 Quando un client si connette al server, il server legge il messaggio inviato 
 dal client e invia un messaggio di risposta.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Ciao, sono il server!";

    // Creazione del socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Impostazione delle opzioni del socket
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Associazione del socket all'indirizzo e alla porta
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Mettere il socket in ascolto delle connessioni in arrivo
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %d...\n", PORT);

    // Accettare le connessioni dei client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Leggere i dati inviati dal client
    valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Messaggio ricevuto dal client: %s\n", buffer);

    // Invio del messaggio di risposta al client
    send(new_socket, response, strlen(response), 0);
    printf("Messaggio inviato al client: %s\n", response);

    // Chiudere le connessioni
    close(new_socket);
    close(server_fd);

    return 0;
}
