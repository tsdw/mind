/* Conversioni di indirizzo */

#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

/*
typedef uint32_t in_addr_t;

struct in_addr {
   in_addr_t s_addr;
};
*/

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Args: IPV4 (Ex: 127.0.0.1)\n");
		exit(1);
	}

	int retcode;

	/* INET_ADDR
	 * in_addr_t inet_addr(const char *cp);
	 * converte l'indirizzo IPV4 (notazione numerica con punti) in numerico intero
	 *
	 * Valori di ritorno:
	 * -1: Se l'indirizzo non e' valido.
	 * (in_addr_t): Se l'indirizzo inserito e' valido ritorna la sua conversione in intero
	 */

	retcode = inet_addr(argv[1]);

	if (retcode == -1) {
		printf("[inet_addr] Errore: indirizzo non valido\n"); 
		exit(1);
	}

	printf("[inet_addr] Indirizzo convertito: %d\n", retcode);

	/* INET_ATON 
	 * int inet_aton(const char *cp, struct in_addr *inp)
	 * converte l'indirizzo IPV4 (notazione numerica con punti) in numerico intero nella struct in_addr
	 *
	 * Valori di ritorno (int):
	 * 0: Se la stringa non e' valida
	 * 1: Se la stringa e' valida
	 */

	struct in_addr net_address;
	retcode = inet_aton(argv[1], &net_address);

	if (retcode == 0){
		printf("[inet_aton] Errore: indirizzo non valido\n");
		exit(1);
	}

	printf("[inet_aton] Indirizzo convertito: %d\n", net_address.s_addr);


	/* INET_NTOA
	 * char *inet_ntoa(struct in_addr in)
	 * Converte l'indirizzo numerico in IPV4
	 * 
	 * Valori di ritorno (char *):
	 * (MAN) The string is returned in a statically  allocated  buffer, which subsequent calls will overwrite.
	 */

	char *ivp4_address = inet_ntoa(net_address);
	printf("%s\n", ivp4_address);

}