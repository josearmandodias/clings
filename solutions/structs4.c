#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *ajouter_tete(Noeud *tete, int valeur)
{
    Noeud *n = malloc(sizeof(*n));
    if (!n) return tete;
    n->valeur  = valeur;
    n->suivant = tete;
    return n;
}

size_t longueur(const Noeud *tete)
{
    size_t n = 0;
    for (const Noeud *c = tete; c; c = c->suivant) n++;
    return n;
}

void liberer(Noeud *tete)
{
    while (tete) {
        Noeud *suivant = tete->suivant;
        free(tete);
        tete = suivant;
    }
}

int main(void)
{
    Noeud *liste = NULL;

    CHECK(longueur(liste) == 0);

    for (int i = 1; i <= 5; i++) {
        liste = ajouter_tete(liste, i);
    }
    CHECK(longueur(liste) == 5);
    CHECK(liste->valeur == 5);
    CHECK(liste->suivant->valeur == 4);

    Noeud *un = ajouter_tete(NULL, 42);
    CHECK(longueur(un) == 1);
    CHECK(un->valeur == 42 && un->suivant == NULL);
    liberer(un);

    liberer(NULL);              /* liberer une liste vide est inoffensif */
    liberer(liste);
    CHECK_NO_LEAK();
    OK("liste chainee");
    return 0;
}
