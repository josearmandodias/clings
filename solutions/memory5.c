#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct {
    int   *data;
    size_t taille;
    size_t capacite;
} Vec;

int vec_push(Vec *v, int valeur)
{
    if (v->taille == v->capacite) {
        size_t nc = v->capacite ? v->capacite * 2 : 4;
        int *tmp = realloc(v->data, nc * sizeof(*v->data));
        if (!tmp) return 0;
        v->data = tmp;
        v->capacite = nc;
    }
    v->data[v->taille++] = valeur;
    return 1;
}

void vec_free(Vec *v)
{
    free(v->data);
    v->data = NULL;
    v->taille = v->capacite = 0;
}

int main(void)
{
    Vec v = {NULL, 0, 0};

    for (int i = 0; i < 100; i++) {
        CHECK(vec_push(&v, i * 3) == 1);
    }
    CHECK(v.taille == 100);
    CHECK(v.capacite >= 100);
    CHECK(v.data[0] == 0);
    CHECK(v.data[99] == 297);

    vec_free(&v);
    CHECK(v.data == NULL);

    Vec w = {NULL, 0, 0};
    CHECK(vec_push(&w, 10) == 1);
    CHECK(w.capacite == 4);          /* premier palier : 0 -> 4 */

    for (int i = 0; i < 4; i++) {
        CHECK(vec_push(&w, i) == 1);
    }
    CHECK(w.taille == 5);
    CHECK(w.capacite == 8);          /* la capacite a double */

    vec_free(&w);
    CHECK_NO_LEAK();
    OK("tableau dynamique avec realloc");
    return 0;
}
