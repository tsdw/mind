
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    int retcode;
    char *pointer;

    // Strings
    char s1[] = "Compare";
    char s2[] = "compare";
    char s3[] = "coMparing";
    char s4[] = "otherstring";

    /*
     * int strcasecmp(const char *s1, const char *s2);
     *
     * The  strcasecmp() function performs a byte-by-byte comparison of the strings s1 and s2, ignoring the case
     * of the characters.
     *
     * Valori di ritorno:
     * < 0: Se s1 < s2
     * = 0: Se s1 = s2
     * > 0: Se s1 > s2
     *
     */

    retcode = strcasecmp(s1, s2);
    printf("strcasecmp (s1 = s2): %d\n", retcode);

    retcode = strcasecmp(s1, s3);
    printf("strcasecmp (s1 < s3): %d\n", retcode);

    retcode = strcasecmp(s3, s1);
    printf("strcasecmp (s1 > s3): %d\n", retcode);


    /*
     *  int strncasecmp(const char *s1, const char *s2, size_t n);
     *
     *  The strncasecmp() function is similar, except that it compares no more than n bytes of s1 and s2.
     *
     *  Valori di ritorno:
     *  Uguale a strcasecmp.
     */

    retcode = strncasecmp(s1, s3, 1);
    printf("strncasecmp (s1 = s3): %d\n", retcode);

    retcode = strncasecmp(s1, s4, 1);
    printf("strncasecmp (s1 != s4) = (s1 < s4): %d\n",
           retcode); // Ritorna -12 perche' nella tabella ascii la lattera 'o' dista di 12 posizioni rispetto alla 'c'


    /*
     * char *index(const char *s, int c);
     *
     * Return a pointer to the first occurrence of the character c in the string s.
     *
     * Valori di ritorno:
     * return a pointer to the matched character or NULL if the character is not found.
     *
     * marked as LEGACY in POSIX.1-2001. POSIX.1-2008 removes the specifications of index() and rindex()
     * recommending: strchr(const char *s, int c);
     *
     */

    pointer = index(s4, 'r');

    if (pointer == NULL) {
        printf("index: character is not found");
    } else {
        printf("index (found): %c\n", *pointer);
    }

    /*
     * char *rindex(const char *s, int c);
     *
     * The rindex() function returns a pointer to the LAST occurrence of the character c in the string s.
     *
     * Valori di ritorno
     * Uguale a index
     *
     * marked as LEGACY in POSIX.1-2001. POSIX.1-2008 removes the specifications of index() and rindex()
     * recommending: strrchr(const char *s, int c);
     */

    pointer = rindex(s4, 'r');

    if (pointer == NULL) {
        printf("rindex: character is not found");
    } else {
        printf("rindex (found): %c, carattere successivo: %c, carattere precedente: %c\n", *pointer, *(pointer+1), *(pointer-1));
    }


    /*
     * char *strcat(char *dest, const char *src);
     *
     * Appends  the  src  string to the dest string, overwriting the terminating null byte ('\0') at the end of dest,
     * and then adds a terminating null byte.
     *
     * N.B: The strings may not overlap, and the dest string must have enough space for the result.
     * If dest is not large enough, program behavior is unpredictable; buffer overruns are a favorite
     * avenue for attacking secure programs.
     *
     * Valori di ritorno:
     * return a pointer to the resulting string dest.
     */

    char extrabuffer[30] = "Oggi sono stato ";
    const char *sfinal = "al mare";

    pointer = strcat(extrabuffer, sfinal);
    printf("strcat: %s\n", pointer);


    /*
     * int strcmp(const char *s1, const char *s2);
     * int strncmp(const char *s1, const char *s2, size_t n);
     *
     * The strcmp() function compares the two strings s1 and s2.
     * The strncmp() function is similar, except it compares only the first (at most) n bytes of s1 and s2.
     *
     * Valori di ritorno:
     * < 0: Se s1 < s2
     * = 0: Se s1 = s2
     * > 0: Se s1 > s2
     *
     */

    retcode = strcmp(s1, s2);
    printf("strcmp (s1 < s2): %d\n", retcode);


    /*
     * char *strcpy(char *dest, const char *src);
     * char *strncpy(char *dest, const char *src, size_t n);
     *
     * The strcpy() function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to by dest.
     * The strncpy() function is similar, except that at most n bytes of src are copied.
     *
     * Valori di ritorno:
     * The strcpy() and strncpy() functions return a pointer to the destination string dest.
     *
     */

    char dest[sizeof s1];
    pointer = strcpy(dest, s1);
    printf("strcpy: %s\n", pointer);

    char sdest[20];
    pointer = strncpy(sdest, s1, 3);
    pointer[3] = '\0'; // Quando si usa strncpy e' necessario aggiungere il carattere di terminazione (in certi casi)
    printf("strncpy: %s\n", pointer);

    /*
     * size_t strlen(const char *s);
     * The strlen() function calculates the length of the string pointed to by s, excluding the terminating null byte ('\0').
     *
     * Valori di ritorno:
     * The strlen() function returns the number of characters in the string pointed to by s.
     *
     */

    retcode = strlen(s1);
    printf("strlen: %d sizeof: %ld \n", retcode, sizeof s1); // Sizeof include il carattere terminatore quindi il risultato sara' piu' grande di uno


    /*
     * char *strdup(const char *s);
     *
     * The strdup() function returns a pointer to a new string which is a duplicate of the string s.
     * N.B: Memory for the new string is obtained with malloc(3), and can be freed with free(3).
     *
     * Valori di ritorno:
     * New string: returns a pointer to the duplicated string
     * NULL: if insufficient memory was available
     */

    char *snew = strdup(s1);
    printf("strdup: %s\n", snew);

    free(snew);
    printf("strdup: %s is NULL\n", snew);


    /*
     * strtok(char *str, const char *delim);
     *
     *  Extract tokens from the string s that are delimited by one of the bytes in delim.
     *  In each subsequent call that should parse the same string, str must be NULL
     *
     *  N.B: A sequence of calls to strtok() that operate on the same string maintains a pointer that determines
     *  the point from which to start searching for the next token.
     *  The first call  to strtok() sets this pointer to point to the first byte of the string.
     *  The start of the next token is determined by scanning forward for the next nondelimiter byte in str.
     *  If such a byte is found, it is taken as the start of the next token.
     *  If no such byte is found, then there are no more tokens, and strtok() returns NULL.
     *  (A string that is empty or  that contains only delimiters will thus cause strtok() to return NULL on the first call.)
     *
     *  Valori di ritorno:
     *  Pointer: to the next token
     *  NULL: if there are no more tokens
     *
     */

    char phrase[] = "Oggi vado a giocare con dio";

    pointer = strtok(phrase, " ");

    while (pointer != NULL){
        printf("strtok: %s\n", pointer);
        pointer = strtok(NULL, " ");
    }
}