/* clings.h — petit harnais de test partagé par tous les exercices.
 *
 * Tu n'as jamais besoin de modifier ce fichier.
 *
 *   CHECK(cond)      -> échoue proprement si cond est fausse
 *   OK("message")    -> affiche une ligne de succès
 *
 * Certains exercices définissent CLINGS_TRACK_ALLOC avant d'inclure ce
 * fichier : malloc/calloc/realloc/free sont alors comptés, et
 * CHECK_NO_LEAK() vérifie qu'il ne reste aucun bloc alloué.
 */
#ifndef CLINGS_H
#define CLINGS_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            fprintf(stderr, "  [X] test echoue : %s   (%s ligne %d)\n",    \
                    #cond, __FILE__, __LINE__);                            \
            exit(1);                                                       \
        }                                                                  \
    } while (0)

#define OK(msg) printf("  [v] %s\n", (msg))

#ifdef CLINGS_TRACK_ALLOC

static long clings__live __attribute__((unused)) = 0;

__attribute__((unused)) static void *clings__malloc(size_t n)
{
    void *p = malloc(n);
    if (p) clings__live++;
    return p;
}

__attribute__((unused)) static void *clings__calloc(size_t n, size_t s)
{
    void *p = calloc(n, s);
    if (p) clings__live++;
    return p;
}

__attribute__((unused)) static void *clings__realloc(void *q, size_t n)
{
    void *p = realloc(q, n);
    if (p && !q) clings__live++;
    return p;
}

__attribute__((unused)) static void clings__free(void *p)
{
    if (p) clings__live--;
    free(p);
}

#define malloc(n)     clings__malloc(n)
#define calloc(n, s)  clings__calloc((n), (s))
#define realloc(p, n) clings__realloc((p), (n))
#define free(p)       clings__free(p)

#define CHECK_NO_LEAK()                                                    \
    do {                                                                   \
        if (clings__live > 0) {                                            \
            fprintf(stderr,                                                \
                    "  [X] fuite memoire : %ld bloc(s) jamais libere(s)\n",\
                    clings__live);                                         \
            exit(1);                                                       \
        }                                                                  \
        if (clings__live < 0) {                                            \
            fprintf(stderr, "  [X] plus de free() que de malloc()\n");     \
            exit(1);                                                       \
        }                                                                  \
    } while (0)

#else
#define CHECK_NO_LEAK() ((void)0)
#endif /* CLINGS_TRACK_ALLOC */

#endif /* CLINGS_H */
