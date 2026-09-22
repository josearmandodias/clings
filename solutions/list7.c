// Trouver le noeud du milieu avec deux pointeurs (l'un avance de 2, l'autre de
// 1). Pour une longueur paire, renvoie le SECOND du milieu ; NULL si vide.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `milieu`.

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

Noeud *milieu(Noeud *tete)
{
    Noeud *lent   = tete;
    Noeud *rapide = tete;

    while (rapide && rapide->suivant) {
        lent   = lent->suivant;
        rapide = rapide->suivant->suivant;
    }
    return lent;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int t[] = {1, 2, 3, 4, 5};
    Noeud *l = depuis_tableau(t, 5);
    const Noeud *m = milieu(l);
    CHECK(m && m->valeur == 3);
    liberer(l);

    int p[] = {1, 2, 3, 4};
    l = depuis_tableau(p, 4);
    m = milieu(l);                   /* paire : le second du milieu */
    CHECK(m && m->valeur == 3);
    liberer(l);

    int u[] = {1};
    l = depuis_tableau(u, 1);
    m = milieu(l);
    CHECK(m && m->valeur == 1);
    liberer(l);

    CHECK(milieu(NULL) == NULL);

    CHECK_NO_LEAK();
    OK("milieu d'une liste");
    return 0;
}
