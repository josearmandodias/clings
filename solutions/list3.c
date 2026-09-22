// Inserer un noeud avant l'element d'indice `index`. Si `index` depasse la
// longueur, l'insertion se fait en queue. La fonction renvoie la nouvelle tete.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `inserer_a`.

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

void liberer(Noeud *tete)
{
    while (tete) { Noeud *s = tete->suivant; free(tete); tete = s; }
}

/* construit une liste dans l'ordre du tableau */
Noeud *depuis_tableau(const int *tab, size_t n)
{
    Noeud *tete = NULL, *queue = NULL;
    for (size_t i = 0; i < n; i++) {
        Noeud *x = malloc(sizeof *x);
        if (!x) { liberer(tete); return NULL; }
        x->valeur = tab[i]; x->suivant = NULL;
        if (queue) queue->suivant = x; else tete = x;
        queue = x;
    }
    return tete;
}

Noeud *inserer_a(Noeud *tete, size_t index, int v)
{
    Noeud *n = malloc(sizeof *n);
    if (!n) return tete;
    n->valeur = v;
    n->suivant = NULL;

    if (!tete || index == 0) {
        n->suivant = tete;
        return n;
    }

    Noeud *courant = tete;
    for (size_t i = 0; i + 1 < index && courant->suivant; i++)
        courant = courant->suivant;

    n->suivant = courant->suivant;
    courant->suivant = n;
    return tete;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int tab[] = {1, 2, 3};
    Noeud *l = depuis_tableau(tab, 3);

    l = inserer_a(l, 0, 0);          /* nouvelle tete : {0,1,2,3} */
    CHECK(l->valeur == 0);
    CHECK(l->suivant && l->suivant->valeur == 1);

    l = inserer_a(l, 2, 9);          /* au milieu : {0,1,9,2,3} */
    const Noeud *c = l;
    CHECK(c && c->valeur == 0); c = c->suivant;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 9); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c == NULL);

    l = inserer_a(l, 5, 7);          /* index == longueur : en queue */
    c = l;
    CHECK(c && c->valeur == 0); c = c->suivant;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 9); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 7 && c->suivant == NULL);

    l = inserer_a(l, 100, 8);        /* index > longueur : en queue aussi */
    c = l;
    while (c && c->suivant) c = c->suivant;
    CHECK(c && c->valeur == 8 && c->suivant == NULL);
    liberer(l);

    Noeud *u = inserer_a(NULL, 0, 42);   /* liste vide, index 0 */
    CHECK(u && u->valeur == 42 && u->suivant == NULL);
    liberer(u);

    CHECK_NO_LEAK();
    OK("inserer a l'index");
    return 0;
}
