#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREAD 2

void *print(void *);

/*
 * A mutex is a MUTual EXclusion device, useful for:
 * 1) protecting shared data structures from concurrent modifications, and
 * 2) implementing critical sections and monitors.
 *
 * A mutex has two possible states:
 * 1) unlocked (not owned by any thread)
 * 2) locked (owned by one thread)
 *
 * A thread attempting to lock a mutex already locked by another thread is
 * uspended until the owning thread unlocks the mutex
 */

int x;
pthread_mutex_t init_static = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t init_func;

int main(int argc, char *argv[]){

    int retcode;

    /*
     * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
     *
     * initializes mutex *mutex according to attributes *mutexattr (set to NULL for default attributes).
     * Types:
     * 1) fast (default)
     * 2) recursive
     * 3) error checking
     *
     * Mutexes can also be initialized statically:
     * pthread_mutex_t fast = PTHREAD_MUTEX_INITIALIZER;
     * pthread_mutex_t rec = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
     * pthread_mutex_t errck= PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
     *
     * N.B: destroys a mutex object, which must be unlocked, freeing the resources it might hold.
     *
     * Valori di ritorno:
     * 0: In caso di successo
     * Other number: In caso di fallimento
     *
     */

    retcode = pthread_mutex_init(&init_func, NULL);

    if (retcode == 0) {
        printf("MUTEX: init success\n");
    }

    /*
     * int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
     *
     * The pthread_mutex_destroy() function shall destroy the mutex object referenced by mutex;
     * the mutex object becomes, in effect, uninitialized.
     * An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value.
     *
     * N.B: A destroyed mutex object can be reinitialized using pthread_mutex_init();
     * the results of otherwise referencing the object after it has been destroyed are undefined.
     *
     * N.B: destroys a mutex object, which must be unlocked, freeing the resources it might hold
     *
     * Valori di ritorno:
     * 0: In caso di successo
     * Other number: In caso di fallimento
     */

    retcode = pthread_mutex_destroy(&init_func);

    if (retcode == 0) {
        printf("MUTEX: destroy success\n");
    }


    // Inizializzazione threads
    pthread_t thread[N_THREAD];

    for (int i=0; i < N_THREAD; i++){
        retcode = pthread_create(&thread[i], NULL, print, (void *) &i);

        if (retcode) {
            printf("Error: %d \n", retcode);
            exit(1);
        }
    }

    pthread_exit(NULL);
}


void *print(void *arg){
    int retcode;
    int tid = *((int *) arg);

    for (;;) {

        printf("THREAD ID: %d\n", tid);

        /*
         * int pthread_mutex_lock(pthread_mutex_t *mutex);
         * int pthread_mutex_trylock(pthread_mutex_t *mutex);
         *
         * The mutex object referenced by mutex shall be locked by calling pthread_mutex_lock().
         * If the mutex is already locked, the calling thread shall block until the mutex becomes available.
         * This operation shall return with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
         *
         * N.B: if the mutex is fast (DEFAULT), the calling thread is suspended until the mutex is unlocked,
         * this effectively causes the calling thread to deadlock!
         *
         * N.B: trylock() behaves identically to lock(), except:
         * it does not block the calling thread if mutex is already locked by another thread (or by the calling thread for a fast mutex)
         * instead, it returns immediately, with error EBUSY
         *
         * Valori di ritorno:
         * 0: In caso di successo
         * Other number: in caso di fallimento
         *
         */


        retcode = pthread_mutex_lock(&init_static);

        if (retcode == 0) {
            printf("THREAD %d: lock\n", tid);
        }

        x++;

        printf("THREAD %d: changed x to %d\n", tid, x);


        /*
         * int pthread_mutex_unlock(pthread_mutex_t *mutex);
         *
         * Unlocks the mutex, assumed to be owned by the calling thread
         *
         * N.B: if the mutex is fast, always returns it to the unlocked state
         *
         * Valori di ritorno:
         * 0: In caso di successo
         * Other number: in caso di fallimento
         *
         */


        retcode = pthread_mutex_unlock(&init_static);

        if (retcode == 0) {
            printf("THREAD %d: unlock\n", tid);
        }
    }
}
