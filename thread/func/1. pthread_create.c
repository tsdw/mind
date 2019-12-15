#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

// La compilazione deve essere effettuata passando come argomento al compilatore la dipendenza lpthread.
// Ex: gcc ex.c -lpthread

// Prototipo funzione
void *my_routine(void *);
void *my_routine2(void *);

int main(int argc, char *argv[]){
	/*
	 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	 *
	 * The  pthread_create()  function  starts  a  new  thread in the calling process.
	 *
	 * The new thread terminates in one of the following ways:
	 * 1) It calls pthread_exit(3)
	 * 2) It returns from start_routine()
	 * 3) It is canceled (see pthread_cancel(3))
	 * 4) ny of the threads in the process calls exit(3) (This cause the termination of all threads)
	 *
	 *
	 * Argomenti:
	 *
	 * 1) Puntatore al tipo thread in cui verra' scritto l'identificatore del thread creato
	 *
	 * 2) Puntatore alla struttura degli attributi del nuovo thread.
	 *    Se vale NULL allora il thread verra' creato con gli attributi di default ovvero: thread joinable e default sheduling policy)
	 *
	 * 3) Puntatore alla funzione che il thread eseguira'
	 *
	 * 4) Puntatore all'argomento da passare alla funzione che verra' eseguita
	 *
	 *
	 * Valori di ritorno:
	 *
	 * O: Se tutto va a buon fine
	 * An error number: Se qualcosa va storto
	 *
	 */

	int retcode;
	pthread_t first;
	pthread_t second;

	retcode = pthread_create(&first, NULL, my_routine, (void *) 1);

	if (retcode != 0) {
	    printf("Errore durnte la creazione del thread\n");
	    exit(1);
	}

	// Metodo alternativo per passare l'argomento
	int arg = 2;
    retcode = pthread_create(&first, NULL, my_routine2, (void *) &arg);

    if (retcode != 0) {
        printf("Errore durnte la creazione del thread\n");
        exit(1);
    }

	/* Differenza pthread exit vs join
	 *
	 * pthread_exit() uscirà dal thread che lo chiama.
	 * Nel tuo caso poiché il main lo chiama, il thread principale terminerà mentre i thread generati continueranno a essere eseguiti.
	 * Questo è usato principalmente nei casi in cui il thread principale è richiesto solo per generare thread e lasciare che i thread facciano il loro lavoro
	 *
	 * pthread_join sospenderà l'esecuzione del thread che lo ha chiamato a meno che il thread di destinazione non termini
	 */

    pthread_exit(NULL);
    // Se al posto ci fosse stato return (o exit) avrebbe chiuso tutti i thread compreso il main senza completare la loro esecuzione
}



/*
 * Funzione: void *(*start_routine) (void *)
 *
 * N.B: void * E' un puntatore generico: Serve a scrivere funzioni ‘polimorfe’.
 *      Viene effettuato un cast implicito per il valore di ritorno e per il tipo passato come argomento della funzione
 *      (Se si vogliono passare piu argomenti si utilizza una struct)
 *
 */

void *my_routine(void *arg){

    /* Per i sistemi a 64 bit:
     *
     * Non e' possibile fare - (int) arg - perche' il puntatore e' a 64 bits mentre int e' a 32bits (il compilatore dara' warning)
     * Tuttavia e' possibile usare - (long) arg - perche' long e' a 64 bits e lo e' pure il puntatore
     *
     * https://stackoverflow.com/questions/26805461/why-do-i-get-cast-from-pointer-to-integer-of-different-size-error
     *
     */

    int n = (uintptr_t) arg;
    printf("Numero del thread: %d\n", n);
    pthread_exit(NULL); // return NULL;
}

void *my_routine2(void *arg){
    // Cast del puntatore void * a int *. Alla fine *(...) estraggo il valore del puntatore
    int n = *((int *)arg);
    printf("Numero del thread: %d\n", n);
    pthread_exit(NULL); // return NULL;
}
