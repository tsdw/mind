// Questo codice non compila, funge solo da spiegazione

/*
 * pthread_cond_t
 *
 * A condition (short for ``condition variable'') is a synchronization device that allows threads
 * to suspend execution and relinquish the processors until some predicate on shared data is satisfied.
 * The basic operations on conditions are: signal the condition (when the predicate becomes true),
 * and wait for the condition, suspending the thread execution until another thread signals the condition.
 *
 * N.B: A condition variable must always be associated with a mutex, to avoid the race condition
 * where a thread prepares to wait on a condition variable and another thread signals the condition
 * just before the first thread actually waits on it.
 *
 *
 * 1) Inizializzazione esplicita
 * pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 *
 * 1.1) Inizializzazione con funzione (implicita)
 * int pthread_cond_init(pthread cond_t *cond, pthread condattr t *cond_attr);
 *
 * Ex:
 * pthread_cond_t cond
 * pthread_cond_init(&cond, NULL); // NULL = Default value = PTHREAD_COND_INITIALIZER
 *
 * 2) Distruzione variabile di condizione
 * int pthread_cond_destroy(pthread cond t *cond);
 *
 * Ex:
 * pthread_cond_t cond
 * pthread_cond_init(cond, NULL);
 * pthread_cond_destroy(&cond);
 *
 */

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Inizializzazione esplicita
pthread_cond_destroy(&cond); // Distruzione

/*
 * int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
 *
 * The pthread_cond_wait() function is used to block on a condition variable.
 * It is called with mutex locked by the calling thread or undefined behaviour will result.
 *
 *
 * N.B: 1. Il thread chiamante si sospende sulla coda associata a cond, e il mutex viene liberato.
 *      2. Al successivo risveglio (provocato da una signal), il thread rioccupera` il mutex automaticamente.
 *
 *
 * Valori di ritorno:
 * 0: Va a buon fine
 * Other number: errore
 *
 */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_wait(&cond, &mutex);



/*
 * int pthread_cond_signal(pthread_cond_t* cond);
 *
 * This functions shall unblock threads blocked on a condition variable
 * The pthread_cond_signal() function shall unblock at least one of the threads that are blocked
 * on the specified condition variable cond (if any threads are blocked on cond).
 *
 * N.B: 1. Se non vi sono thread sospesi sulla condizione, la signal non ha effetto
 *
 *      2. If more than one thread is blocked on a condition variable, the scheduling policy
 *          shall determine the order in which threads are unblocked.
 *
 *      3. Per risvegliare tutti i thread sospesi su una variabile condizione si usa:
 *          int pthread_cond_broadcast(pthread_cond_t* cond);
 *
 *
 * Valori di ritorno:
 * 0: Va a buon fine
 * Other number: errore
 *
 */

pthread_cond_signal(&cond); // Sveglia un solo thread messo in attesa nella variabile cond
pthread_cond_broadcast(&cond); // Sveglia tutti i thread messi in attesa sulla variabile cond

