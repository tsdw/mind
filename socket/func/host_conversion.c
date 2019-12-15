/*
 * Conversione numerica di long e short
 * Convertono un long/short dal formato locale a quello di rete (Network byte order)
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Args: Number (Ex: 9000)\n");
        exit(1);
    }

    /*
     * uint32_t htonl(uint32_t hostlong);
     * Converte un long dal formato locale a quello di rete
     *
     * Valore di ritorno:
     * Numero convertito
     */

    printf("Host long to net long: %d\n", htonl(atoi(argv[1])));

    /*
     * uint16_t htons(uint16_t hostshort);
     * Converte uno short dal formato locale a quello di rete
     *
     * Valore di ritorno:
     * Numero convertito
     */

    printf("Host short to net short: %d\n", htons(atoi(argv[1])));

    /*
     * uint32_t ntohl(uint32_t netlong);
     * Converte un long dal formato di rete a quello locale
     *
     * Valore di ritorno:
     * Numero convertito
     */

    printf("Net long to host long: %d\n", ntohl(htonl(atoi(argv[1]))));


    /*
     * uint16_t ntohs(uint16_t netshort);
     * Converte uno short dal formato di rete a quello locale
     *
     * Valore di ritorno:
     * Numero convertito
     */

    printf("Net short to host short: %d\n", ntohs(htons(atoi(argv[1]))));
}
