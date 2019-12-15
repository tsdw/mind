// Questo codice non compila (serve solo per la spiegazione)


// Supponiamo che questa sia la funzione eseguita da thread_create
void *timer(void *arg){

    /*
     * int pthread_cancel(pthread_t thread);
     *
     * Manda una richiesta di terminazione al thread che viene passato come argomento
     *
     * N.B: il thread
     *  ignora la richiesta se: PTHREAD CANCEL DISABLE
     *  accetta la richiesta se: PTHREAD CANCEL ENABLE (Default alla creazione del thread) e ritorna: PTHREAD CANCELED per un eventuale pthread_join
     *
     *
     * Stato e tipo di cancellazione si manipolano con:
     *
     * int pthread_setcancelstate(int state,int *oldstate); (Abilita o disabilita la cancellazione)
     * int pthread_setcanceltype(int type,int *oldtype); (Modalita' di cancellazione DEFERRED (default) o ASYNCHRONOUS)
     *
     * Dove oldstate e oldtype possono essere NULL
     *
     *
     * Valori di ritorno:
     * 0: Se la richiesta di cancellazione va a buon fine
     * Non zero: se la richiesta non puo' essere soddisfatta
     *
     */

    pthread_cancel(pthread_self());
}
