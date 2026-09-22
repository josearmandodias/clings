// Dans un tableau TRIE, la recherche binaire elimine la moitie des candidats
// a chaque etape : on regarde le milieu, puis on restreint la recherche a la
// moitie gauche ou droite.
//
// Calcule le milieu avec `debut + (fin - debut) / 2` plutot que
// `(debut + fin) / 2`, pour eviter tout debordement.
//
// `recherche_binaire` renvoie l'indice de `cible`, ou -1 si elle est absente.


// I AM NOT DONE

#include "clings.h"

int recherche_binaire(const int *tab, size_t n, int cible)
{
    /* TODO */
    (void)tab;
    (void)n;
    (void)cible;
    return -1;
}

int main(void)
{
    int t[] = {1, 3, 5, 7, 9, 11};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(recherche_binaire(t, 6, 7) == 3);
    CHECK(recherche_binaire(t, 6, 1) == 0);
    CHECK(recherche_binaire(t, 6, 11) == 5);
    CHECK(recherche_binaire(t, 6, 4) == -1);
    CHECK(recherche_binaire(t, 1, 1) == 0);
    CHECK(recherche_binaire(t, 0, 7) == -1);
    OK("recherche binaire");
    return 0;
}
