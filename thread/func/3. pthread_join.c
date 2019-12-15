#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *timer (void *);

int main(int argc, char *argv[]){
    int retcode;
    int number;

    // Creazione primo thread
    pthread_t first;

    number = 1;
    retcode = pthread_create(&first, NULL, timer, (void *) &number);

    if (retcode != 0) {
        printf("THREAD: Create error.\n");
        exit(1);
    }

    // Creazione secondo thread
    pthread_t second;

    number = 2;
    retcode = pthread_create(&second, NULL, timer, (void *) &number);

    if (retcode != 0) {
        printf("THREAD: Create error.\n");
        exit(1);
    }

    /*
     * int pthread_join(pthread_t thread, void **retval);
     *
     * Attende la terminazione di thread.
     *
     * 1. N.B: E' una funzione bloccante poiche' il thread principale (in questo caso il main) attende la fine dell'esecuzione dell'esecuzione
     *  del thread di cui effettua la join.
     *
     * 2. N.B: pthread_join deve essere sempre utilizzato per ogni thread che l'applicazione crea.
     *  In questo modo il sistema puo' liberare le risorse impiegate dal thread (Evita il memory leak)
     *
     * Valori di ritorno:
     * 0: Se ha successo, ritorna 0 e un puntatore al valore ritornato dal thread
     * Error code: in caso di fallimento
     */

    // Primo thread
    retcode = pthread_join(first, NULL);

    if (retcode != 0)
        printf("THREAD (1): Join error.\n");

    printf ("THREAD (1): terminato.\n");


    // Secondo thread
    retcode = pthread_join(second, NULL);

    if (retcode != 0)
        printf("THREAD (2): Join error.\n");

    printf ("THREAD (2): terminato.\n");

}

void *timer(void *arg){
    int n = *((int *) arg);
    sleep(2); // unistd.h

    /*
     *  void pthread_exit(void *retval);
     *
     *  The  pthread_exit()  function  terminates  the calling thread and returns a value via retval that
     *  (if the thread is joinable) is available to another thread in the same process that calls pthread_join(3).
     *
     *  N.B: To  allow other threads to continue execution, the main thread should terminate by calling pthread_exit()
     *  rather than exit(3).
     *
     *  N.B: Eseguendo un ritorno dalla funzione (RETURN) si ottiene una chiamata implicita a pthread_exit
     */

    pthread_exit(NULL);
}
