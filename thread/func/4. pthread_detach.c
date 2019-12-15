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
     * int pthread_detach(pthread_t thread);
     *
     * Separa (detach) il thread dal thread principale (in questo caso dal main).
     * Quando un thread detached finisce le risorse vengono liberate automaticamente
     *
     * N.B: !!!! Se il thread principale (main) utilizza exit() vengono chiusi anche i thread detach !!!!
     *
     * Valori di ritorno:
     * 0: In caso di successo
     * Error number: in caso di errore
     *
     * N.B: A differenza di pthread_join non e' bloccante
     *
     * N.B: Either pthread_join(3) or pthread_detach() should be called for each thread that an application  creates,
     * so that system resources for the thread can be released.  (But note that the resources of any threads for
     * which one of these actions has not been done will be freed when the process terminates.)
     *
     * Valori di ritorno:
     * 0: Se ha successo, ritorna 0 e un puntatore al valore ritornato dal thread
     * Error code: in caso di fallimento
     *
     */

    // Primo thread
    retcode = pthread_detach(first);

    if (retcode != 0)
        printf("THREAD (1): Join error.\n");

    // Secondo thread
    retcode = pthread_detach(second);

    if (retcode != 0)
        printf("THREAD (2): Detach error.\n");

    pthread_exit(NULL); // N.B!!!!!! Esce solo dal thread da cui viene usata (thread principale main) senza chiudere gli altri thread
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

    printf ("THREAD (%d): terminato.\n", n);
    pthread_exit(NULL);
}
