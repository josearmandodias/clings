// Inverser une liste chainee de facon RECURSIVE (sans aucune boucle).
//
// `depuis_tableau` et `liberer` sont fournies. Complete `inverser_rec`.


// I AM NOT DONE

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

Noeud *inverser_rec(Noeud *tete)
{
    /* TODO */
    return tete;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int t[] = {1, 2, 3};
    Noeud *l = depuis_tableau(t, 3);
    l = inverser_rec(l);
    const Noeud *c = l;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c == NULL);
    liberer(l);

    int u[] = {7};
    l = depuis_tableau(u, 1);
    l = inverser_rec(l);
    CHECK(l && l->valeur == 7 && l->suivant == NULL);
    liberer(l);

    CHECK(inverser_rec(NULL) == NULL);

    CHECK_NO_LEAK();
    OK("inverser recursivement");
    return 0;
}
