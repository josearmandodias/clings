// Construire une liste chainee a partir d'un tableau, puis compter ses noeuds.
//
// `liberer` est fournie. Complete `depuis_tableau` (renvoie la tete de la liste
// construite dans l'ordre du tableau) et `longueur` (renvoie le nombre de noeuds).


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

Noeud *depuis_tableau(const int *tab, size_t n)
{
    /* TODO */
    (void)tab;
    (void)n;
    return NULL;
}

size_t longueur(const Noeud *tete)
{
    /* TODO */
    (void)tete;
    return 0;
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
