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

void liberer_arbre(Arbre *racine)
{
    if (!racine) return;
    liberer_arbre(racine->gauche);
    liberer_arbre(racine->droite);
    free(racine);
}

size_t infixe(const Arbre *racine, int *sortie)
{
    if (!racine) return 0;

    size_t n = infixe(racine->gauche, sortie);
    sortie[n] = racine->valeur;
    return n + 1 + infixe(racine->droite, sortie + n + 1);
}

int main(void)
{
    Arbre *a = NULL;
    int    sortie[8] = {0};

    CHECK(infixe(a, sortie) == 0);   /* arbre vide */

    a = inserer(a, 5);
    a = inserer(a, 3);
    a = inserer(a, 8);
    a = inserer(a, 1);

    size_t n = infixe(a, sortie);
    CHECK(n == 4);
    CHECK(sortie[0] == 1);
    CHECK(sortie[1] == 3);
    CHECK(sortie[2] == 5);
    CHECK(sortie[3] == 8);

    liberer_arbre(a);
    CHECK_NO_LEAK();
    OK("parcours infixe");
    return 0;
}
