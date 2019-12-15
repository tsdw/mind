
#include<stdio.h>
#include<stdlib.h>

int main(int argv, char *argc[]){
    char s1[] = "1000";
    char s2[] = "tr50";

    /*
     * Conversione stringa a intero
     *
     * int atoi(const char *nptr); N.B: Meglio usare strtol
     *
     * The atoi() function converts the initial portion of the string pointed to by nptr to int.
     *
     * Valori di ritorno:
     * int: valore convertito
     *
     */


    printf("atoi: %d \n", atoi(s1));
    printf("atoi: %d \n", atoi(s2)); // s2 non viene convertita perche' contiene delle lettere


    /* Conversione stringa ad intero
     *
     * long int strtol(const char *nptr, char **endptr, int base);
     *
     * The strtol() function converts the initial part of the string in nptr to a long integer value according to the given base,
     * which must be between 2 and 36 inclusive, or be the spe‐cial value 0.
     *
     * Valori di ritorno:
     * The strtol() function returns the result of the conversion, unless the value would underflow or overflow.
     */

    char *ptr;
    int cnvtoint = strtol(s1, &ptr, 10);

    printf("strtol: %d\n", cnvtoint);

    /*
     * Conversione intero a stringa
     *
     * int snprintf(char *str, size_t size, const char *format, ...);
     *
     * The function snprintf() write at most size bytes (including the terminating null byte ('\0')) to str.
     *
     * Valori di ritorno:
     * Upon successful return, these functions return the number of characters printed (excluding the null byte used to end output to strings).
     *
     */

    char sbuff[10];
    int length = snprintf(sbuff, sizeof sbuff, "%d", 13109);
    printf("snprintf: %s\n", sbuff);
}