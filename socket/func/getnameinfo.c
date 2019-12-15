
/* Questa funzione sostituisce gethostbyaddr (obsoleta) e getservbyport (obsoleta)
 * https://beej.us/guide/bgnet/html/multi/getnameinfoman.html
 *
 * NI_MAXHOST: (Lunghezza massima del nome degli host definita in netdb.h)
 * NI_MAXSERV: (Lunghezza massima del servizio - getservbyport)
 *
 * Per svolgere anche il ruolo di getservbyport e' necessario utilizzare gli argomenti serv e servlen
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]) {

	/* GETNAMEINFO
	 * int getnameinfo(const struct sockaddr *sa, socklen_t salen,
                char *host, size_t hostlen,
                char *serv, size_t servlen, int flags);
		
     * Prende l'indirizzo ipv4 (Si usa una struct sockaddr_in e si fa il cast a sockaddr quando si passa come argomento)
     * e restituisce il nome dell'host interrogando il DNS. 
     *
     * Quando la query ricava il nome dell'host lo inserisce in char *host
     *
     * Valori di ritorno:
     * 0: Se la query e' andata a buon fine
     * Other: altri valori di qualcosa e' andato storto
	 */

	if (argc != 2) {
		printf("Args: IPV4 (Ex: 127.0.0.1)\n");
		exit(1);
	}

	int retcode;
	struct sockaddr_in address;

	// Risultato della query (nome dell'host)
	char host[NI_MAXHOST];

	// Configurazione dell'address
	address.sin_family = AF_INET;
	address.sin_port = 9000;
	address.sin_addr.s_addr = inet_addr(argv[1]);

	// Query
	retcode = getnameinfo((struct sockaddr*) &address, sizeof address, host, sizeof host, NULL, 0, 0);

	if (retcode != 0) {
		printf("Qualcosa e' andato storto.\n");
		exit(1);
	}

	printf("%s\n", host);
}
