// Construire une liste chainee a partir d'un tableau, puis compter ses noeuds.
//
// `liberer` est fournie. Complete `depuis_tableau` (renvoie la tete de la liste
// construite dans l'ordre du tableau) et `longueur` (renvoie le nombre de noeuds).

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

size_t longueur(const Noeud *tete)
{
    size_t n = 0;
    while (tete) { n++; tete = tete->suivant; }
    return n;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int tab[] = {1, 2, 3};
    Noeud *liste = depuis_tableau(tab, 3);
    CHECK(longueur(liste) == 3);
    CHECK(liste->valeur == 1);
    CHECK(liste->suivant->valeur == 2);
    CHECK(liste->suivant->suivant->valeur == 3);
    CHECK(liste->suivant->suivant->suivant == NULL);
    liberer(liste);

    Noeud *vide = depuis_tableau(NULL, 0);
    CHECK(vide == NULL);
    CHECK(longueur(vide) == 0);
    liberer(vide);

    liberer(NULL);
    CHECK_NO_LEAK();
    OK("construire et mesurer une liste");
    return 0;
}
