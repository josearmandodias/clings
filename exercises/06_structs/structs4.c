// La liste chaînée : le "hello world" des structures de données en C, parce
// qu'elle force à manier allocation, pointeurs et propriété en même temps.
//
// Complète `ajouter_tete`, `longueur` et `liberer`.
// `ajouter_tete` renvoie la nouvelle tête (ou l'ancienne si malloc échoue).


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *ajouter_tete(Noeud *tete, int valeur)
{
    /* TODO */
    (void)valeur;
    return tete;
}

size_t longueur(const Noeud *tete)
{
    /* TODO */
    (void)tete;
    return 0;
}

void liberer(Noeud *tete)
{
    /* TODO: attention a ne pas lire ->suivant apres avoir libere le noeud */
    (void)tete;
}

int main(void)
{
    Noeud *liste = NULL;

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
