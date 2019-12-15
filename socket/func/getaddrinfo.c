
/* Questa funzione sostituisce gethostbyname (deprecata) e getservbyname (deprecata)
 * Per svolgere anche il ruolo di getservbyname e' necessario passare il nome o la porta del servizio come secondo argomento (const char *service)
 * attualmente tale parametro e' settato a NULL
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]){

	/* GETADDRINFO
	 * int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints,
                       struct addrinfo **res);
     *
     * Restituisce informazioni su un particolare nome host (indirizzo ip o dominio) interrogando un DNS.
	 * Riempie la struttura addrinfo con le informazioni dell'host utilizzando l'indirizzo ipv4
	 *
	 *	struct addrinfo {
			int              ai_flags;
			int              ai_family;
			int              ai_socktype;
			int              ai_protocol;
			socklen_t        ai_addrlen;
			struct sockaddr *ai_addr;
			char            *ai_canonname;
			struct addrinfo *ai_next;
		};
	 *
     * Valori di ritorno:
     * 0: Se la query e' andata a buon fine
     * Other: altri valori di qualcosa e' andato storto
	 */

	if (argc != 2) {
		printf("Args: IPV4 (Ex: 127.0.0.1 or google.it)\n");
		exit(1);
	}

	int retcode;
	struct addrinfo *_addrinfo;

	// DNS Lookup
	retcode = getaddrinfo(argv[1], NULL, NULL, &_addrinfo);

	if (retcode != 0) {
		printf("Qualcosa e' andato storto.\n");
		exit(1);
	}

	// Typecasting di struct sockaddr in sockaddr_in per poter accedere all'indirizzo
	struct sockaddr_in *address_in = (struct sockaddr_in *) _addrinfo->ai_addr;

	// Estrazione dei risultati in (addrinfo)
	printf(" %d\n %d\n %d\n %d\n %s\n %d\n", 	_addrinfo->ai_flags,
												_addrinfo->ai_family, 
												_addrinfo->ai_socktype, 
												_addrinfo->ai_protocol,
												inet_ntoa(address_in->sin_addr),
												address_in->sin_port);
}