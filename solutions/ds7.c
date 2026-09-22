#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Arbre {
    int            valeur;
    struct Arbre  *gauche;
    struct Arbre  *droite;
} Arbre;

Arbre *inserer(Arbre *racine, int v)
{
    if (!racine) {
        Arbre *n = malloc(sizeof(*n));
        if (!n) return NULL;
        n->valeur = v;
        n->gauche = NULL;
        n->droite = NULL;
        return n;
    }

    if (v < racine->valeur)
        racine->gauche = inserer(racine->gauche, v);
    else if (v > racine->valeur)
        racine->droite = inserer(racine->droite, v);

    return racine;
}

int contient(const Arbre *racine, int v)
{
    while (racine) {
        if (v == racine->valeur) return 1;
        racine = (v < racine->valeur) ? racine->gauche : racine->droite;
    }
    return 0;
}

void liberer_arbre(Arbre *racine)
{
    if (!racine) return;
    liberer_arbre(racine->gauche);
    liberer_arbre(racine->droite);
    free(racine);
}

int main(void)
{
    Arbre *a = NULL;

    CHECK(contient(a, 5) == 0);   /* arbre vide */

    a = inserer(a, 5);
    a = inserer(a, 3);
    a = inserer(a, 8);
    a = inserer(a, 1);

    CHECK(contient(a, 5) == 1);
    CHECK(contient(a, 3) == 1);
    CHECK(contient(a, 8) == 1);
    CHECK(contient(a, 1) == 1);
    CHECK(contient(a, 4) == 0);
    CHECK(contient(a, 99) == 0);

    /* structure attendue de l'ABR */
    CHECK(a && a->valeur == 5);
    CHECK(a->gauche && a->gauche->valeur == 3);
    CHECK(a->gauche->gauche && a->gauche->gauche->valeur == 1);
    CHECK(a->droite && a->droite->valeur == 8);

    liberer_arbre(a);
    CHECK_NO_LEAK();
    OK("arbre binaire de recherche");
    return 0;
}
