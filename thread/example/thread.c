#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int m;

// Condition vars
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

// Thread funcs prototype
void *p1 (void *);
void *p2 (void *);

// Main
int main(int argc, char *argv[]){
    int retcode;

    // Random number (Compreso tra 1 e 10)
    srand(time(0));
    m = (rand() % 10) + 1;

    // Thread p1
    pthread_t thread1;

    if ((retcode = pthread_create(&thread1, NULL, p1, NULL)) != 0) {
        printf("THREAD 1: Create error.\n");
    }

    // Thread p2
    pthread_t thread2;

    if ((retcode = pthread_create(&thread2, NULL, p2, NULL)) != 0) {
        printf("THREAD 2: Create error.\n");
    }

    // Close main thread
    pthread_exit(NULL);
}

// Thread 1
void *p1(void *args) {
    for (;;) {
        // Inizio sezione critica
        pthread_mutex_lock(&mutex);

        if (m >= 1 && m <= 5) {
            m = (rand() % 10) + 1;

            /*
             * Sveglia thread2
             *
             * N.B: Il thread2 viene svegliato quando thread1 esce dalla sezione critica con pthread_mutex_unlock(&mutex);
             *      Se non ci fosse pthread_mutex_unlock(&mutex); si verificherebbe deadlock (thread2 non
             *      riuscirebbe piu' a prendere il controllo sulla mutex)
             */

            pthread_cond_signal(&cond2);
            printf("T: P1 M: %d\n", m);

        } else if (m >= 6 && m <= 10) {
            // Il thread1 si mette in attesa (wait e' bloccante)
            pthread_cond_wait(&cond1, &mutex);
        }

        // Fine sezione critica
        pthread_mutex_unlock(&mutex);
    }
}

// Thread 2
void *p2(void *args) {
    for (;;) {
        // Inizio sezione critica
        pthread_mutex_lock(&mutex);

        if (m >= 1 && m <= 5) {
            // Il thread2 si mette in attesa
            pthread_cond_wait(&cond2, &mutex);

        } else if (m >= 6 && m <= 10) {
            m = (rand() % 10) + 1;

            // Sveglia thread1
            pthread_cond_signal(&cond1);
            printf("T: P2 M: %d\n", m);
        }

        // Fine sezione critica
        pthread_mutex_unlock(&mutex);
    }
}