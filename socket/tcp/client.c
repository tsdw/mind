/* Client */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SIZE_BUFFER 1024

int main(int argc, char *argv[]){
	// Args
	if (argc < 3) {
		perror("Error: Needed two args (ip port)");
		exit(1);
	}

	// Return code
	int retcode;

	// Socket
	int client_socket;

	// Address
	struct sockaddr_in server_addr;

	// Buffer
	char buffer[SIZE_BUFFER];

	// Creazione della socket (Descrittore)
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (client_socket == -1){
		perror("Error: creating client socket"); 
		exit(1);
	}

	// Server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	// Tentativo di connessione al server
	int connection = connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

	if (connection == -1){
		perror("Error: Impossibile raggiungere il server");
		exit(1);
	}
	else {
		printf("Connessione al server riuscita \n");
	}

	while(1) {

	    // Input
		printf("Inserisci il titolo: ");
		fgets(buffer, SIZE_BUFFER, stdin);

		// Write
		retcode = write(client_socket, buffer, strlen(buffer));

        if (retcode == -1){
            close(client_socket);
            perror("Error: cannot write");
        }

        // Read
        retcode = read(client_socket, buffer, SIZE_BUFFER - 1); // Riserviamo un byte per settarlo a NULL

        if (retcode > 0) {
            buffer[retcode] = '\0';
            printf("S: %s", buffer);
        }

        else if (retcode == 0 || errno == EPIPE) {
            printf("Server connection closed\n");
            close(client_socket);
            break;
        }

        else if (retcode == -1){
            perror("Error: reading");
        }
	}

	return 0;
}
