// Savoir si une valeur est presente et atteindre un element par son index.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `contient` (1 si v est
// dans la liste, 0 sinon) et `kieme` (ecrit dans *out l'element d'indice k, base
// 0, et renvoie 1 ; renvoie 0 sans toucher *out si l'element n'existe pas).

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

int contient(const Noeud *tete, int v)
{
    for (const Noeud *c = tete; c; c = c->suivant)
        if (c->valeur == v) return 1;
    return 0;
}

int kieme(const Noeud *tete, size_t k, int *out)
{
    const Noeud *c = tete;
    while (c && k > 0) { c = c->suivant; k--; }
    if (!c) return 0;
    *out = c->valeur;
    return 1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int tab[] = {10, 20, 30};
    Noeud *liste = depuis_tableau(tab, 3);

    CHECK(contient(liste, 10));
    CHECK(contient(liste, 30));
    CHECK(!contient(liste, 99));

    int v = -1;
    CHECK(kieme(liste, 0, &v) == 1 && v == 10);
    CHECK(kieme(liste, 2, &v) == 1 && v == 30);
    v = 777;
    CHECK(kieme(liste, 3, &v) == 0);
    CHECK(v == 777);
    liberer(liste);

    CHECK(!contient(NULL, 5));
    v = 42;
    CHECK(kieme(NULL, 0, &v) == 0);
    CHECK(v == 42);

    CHECK_NO_LEAK();
    OK("rechercher et acceder");
    return 0;
}
