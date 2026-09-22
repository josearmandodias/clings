// Une pile (stack) est une structure LIFO : le dernier element empile est le
// premier depile. Sa taille etant inconnue a l'avance, on alloue un tableau
// dynamique et on double sa capacite quand il est plein.
//
// Complete `pile_push`, `pile_pop` et `pile_free`.
// `pile_push` renvoie 1 (ou 0 si l'allocation echoue) ; `pile_pop` renvoie 1,
// ou 0 si la pile est vide, sans toucher a `*v`.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct {
    int   *data;
    size_t taille;
    size_t capacite;
} Pile;

int pile_push(Pile *p, int v)
{
    /* TODO */
    (void)p;
    (void)v;
    return 0;
}

int pile_pop(Pile *p, int *v)
{
    /* TODO */
    (void)p;
    (void)v;
    return 0;
}

void pile_free(Pile *p)
{
    /* TODO */
    (void)p;
}

int main(void)
{
    Pile p = {NULL, 0, 0};
    int  v = 0;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(pile_pop(&p, &v) == 0);   /* pile vide */
    CHECK(v == 0);                  /* *v ne doit pas etre modifie */

    CHECK(pile_push(&p, 1) == 1);
    CHECK(pile_push(&p, 2) == 1);
    CHECK(pile_push(&p, 3) == 1);

    CHECK(pile_pop(&p, &v) == 1 && v == 3);   /* LIFO */
    CHECK(pile_pop(&p, &v) == 1 && v == 2);
    CHECK(pile_pop(&p, &v) == 1 && v == 1);
    CHECK(pile_pop(&p, &v) == 0);

    /* la capacite doit grandir bien au-dela du premier bloc */
    for (int i = 0; i < 100; i++) CHECK(pile_push(&p, i) == 1);
    for (int i = 99; i >= 0; i--)  CHECK(pile_pop(&p, &v) == 1 && v == i);

    pile_free(&p);
    CHECK_NO_LEAK();
    OK("pile dynamique");
    return 0;
}
