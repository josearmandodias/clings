// Le tableau dynamique : la structure que tu réécriras cent fois en C, et
// que Rust te donne gratuitement sous le nom de Vec<T>.
//
// Complète `vec_push`. Stratégie classique : quand capacite est atteinte,
// doubler (0 -> 4 -> 8 -> 16 ...) avec realloc.
//
// Deux pièges :
//   - `realloc(p, n)` peut renvoyer NULL sans libérer p : ne jamais écrire
//     `p = realloc(p, n)` directement, tu perdrais le bloc.
//   - la taille à allouer est `nouvelle_capacite * sizeof(*v->data)`,
//     pas sizeof(v->data) qui est la taille d'un pointeur.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct {
    int   *data;
    size_t taille;
    size_t capacite;
} Vec;

int vec_push(Vec *v, int valeur)
{
    /* TODO: agrandir si besoin, puis ajouter. 1 = succes, 0 = echec. */
    (void)v;
    (void)valeur;
    return 0;
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

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
