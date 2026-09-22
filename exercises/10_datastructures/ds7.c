// Un arbre binaire de recherche (ABR) range les plus petits a gauche et les
// plus grands a droite. L'insertion et la recherche sont recursives ; la
// liberation doit etre faite en POSTORDRE (les fils avant le noeud), sinon on
// perd l'acces aux sous-arbres.
//
// Complete `inserer`, `contient` et `liberer_arbre`.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Arbre {
    int            valeur;
    struct Arbre  *gauche;
    struct Arbre  *droite;
} Arbre;

Arbre *inserer(Arbre *racine, int v)
{
    /* TODO */
    (void)v;
    return racine;
}

int contient(const Arbre *racine, int v)
{
    /* TODO */
    (void)racine;
    (void)v;
    return 0;
}

void liberer_arbre(Arbre *racine)
{
    /* TODO */
    (void)racine;
}

int main(void)
{
    Arbre *a = NULL;

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
