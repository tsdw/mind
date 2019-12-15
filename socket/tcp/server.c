#include <stdio.h>		
#include <errno.h>
#include <string.h>		
#include <stdlib.h> 	
#include <unistd.h> 	
#include <arpa/inet.h>	
#include <sys/types.h>	
#include <sys/socket.h>	

#define SERVER_PORT 9999 
#define SIZE_BUFFER 1024

int main(int argc, char *argv[]){
	
	int retcode;
	int server_sock, client_sock;

	// Address
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	// Buffer 
	char buffer[SIZE_BUFFER];

	// Creazione del file descrittore socket
	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror ("Error: opening server socket");
		exit(1);
	}

	// Configurazione del server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVER_PORT); 

	// Binding
	retcode = bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr));

	if (retcode == -1) {
		perror("Error: binding address");
		exit(1);
	}

	// Listening
	retcode = listen(server_sock, 1); 

	if (retcode == -1) {
		perror("Error: listening");
		exit(1);
	}

	// Accept: se il client si disconnette si rimette in attesa di altre connessioni
	while (1) {
		client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_len);

		if (client_sock == -1){
			perror("Error: accepting client connection");
			close(server_sock);
			exit(1);
		}

		printf("Client connected.\n");

		// Read data from client sock
		while (1) { 
			retcode = read(client_sock, buffer, SIZE_BUFFER - 1); // Riserviamo un byte per settarlo a NULL

			if (retcode > 0) {
				buffer[retcode] = '\0';
				printf("C: %s", buffer);

				// Se il messaggio del client e' stato ricevuto inoltra il messaggio al client
				retcode = write(client_sock, buffer, strlen(buffer));

				if (retcode == -1) {
					close(client_sock);
					perror("Error: cannot write");
				}
			}

			else if (retcode == 0 || errno == EPIPE) {
				printf("Client connection closed: %d\n", client_sock);
				close(client_sock);
				break;
			}

			else if (retcode == -1){
				perror("Error: reading");
			}
		}
	}

	close(server_sock);
	return 0;
}

