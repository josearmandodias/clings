#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct {
    int   *data;
    size_t taille;
    size_t capacite;
} Pile;

int pile_push(Pile *p, int v)
{
    if (p->taille == p->capacite) {
        size_t nc = p->capacite ? p->capacite * 2 : 4;
        int   *tmp = realloc(p->data, nc * sizeof(*tmp));
        if (!tmp) return 0;
        p->data     = tmp;
        p->capacite = nc;
    }
    p->data[p->taille++] = v;
    return 1;
}

int pile_pop(Pile *p, int *v)
{
    if (p->taille == 0) return 0;
    *v = p->data[--p->taille];
    return 1;
}

void pile_free(Pile *p)
{
    free(p->data);
    p->data     = NULL;
    p->taille   = 0;
    p->capacite = 0;
}

int main(void)
{
    Pile p = {NULL, 0, 0};
    int  v = 0;

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
