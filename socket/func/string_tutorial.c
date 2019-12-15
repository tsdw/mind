/* Funzioni utili per la gestione delle stringhe */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *args[]){

    /*
     * In C una stringa e' un vettore di caratteri in cui l'ultimo elemento e'
     * un carattere termininatore rappresentato dal carattere '\0'
     *
     * ULTERIORI CONSIDERAZIONI: (https://www.arduino.cc/reference/en/language/variables/data-types/string/)
     * Generally, strings are terminated with a null character (ASCII code 0).
     * This allows functions (like Serial.print() (in questo caso printf("%s", var)) to tell where the end of a string is.
     * Otherwise, they would continue reading subsequent bytes of memory that aren’t actually part of the string.
     */

    /*
     * Dichiarazione manuale della stringa (IMPORTANTISSIMO: Bisogna aggiungere il carattere terminatore manualmente)
     * NB: Fare attenzione all'uso del singolo apice 'H' quando si assegna carattere per carattere
     */

    char what[] = {'H', 'e', 'l', 'l', 'o', '\0'};

    // Classica dichiarazione della stringa, viene aggiunto in automatico '\0' alla fine della stringa

    char name[] = "Antonino";

    // N.B: Quando non viene definita la grandezza dell'array il compilaratore al momento della compilazione assegna automaticamente la grandezza

    printf("%s %s \n" , what, name);

    /*
     * Dichiarare una stringa e lasciare che sia il compilatore ad aggiungere il carattere terminatore
     * E' necessario dichiarare la grandezza dell'array maggiore (anche di uno) della lunghezza della stringa
     * in modo che il compilatore possa aggiungere automaticamente il carattere terminatore
     *
     * E' un errore dichiarare when[4] = {'O', 'g', 'g', 'i'}; quando si vuole dichiarare una stringa
     * in quanto il compilatore non riuscirebbe ad aggiungere il carattere terminatore perche'
     * non avrebbe lo spazio necessario.
     */

    char when[5] = {'O', 'g', 'g', 'i'}; // Dato che la grandezza della var when e' 5 il compilatore risolve automaticamente il carattere di terminazione
    printf ("%s", when);

    // Dichiarazioni di stringhe altrettanto valide:

    char surname[9] = "Calvagno"; // Calvagno e' lungo 8 lettere e' necessario aggiungere un ulteriore byte per il carattere terminatore. Quindi surname[8 + 1]
    char another[20] = "Calvagno"; // Altrettanto valido anche aggiungendo extrabytes.
}