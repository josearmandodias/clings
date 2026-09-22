// La recherche dichotomique se prête bien à la récursion. L'intervalle de
// recherche est noté [debut, fin) : `fin` est exclu.
//
//   - intervalle vide (debut >= fin) : renvoyer -1 ;
//   - comparer la cible à tab[milieu], avec milieu = debut + (fin - debut)/2 ;
//   - sinon rappeler sur la moitié gauche ou droite.
//
// Le tableau est trié par ordre croissant. Écris `recherche_binaire_rec`.


// I AM NOT DONE

#include "clings.h"

int recherche_binaire_rec(const int *tab, int debut, int fin, int cible)
{
    /* TODO */
    (void)tab;
    (void)debut;
    (void)fin;
    (void)cible;
    return -1;
}

int main(void)
{
    int tab[] = {1, 3, 5, 7, 9, 11};
    int n = (int)(sizeof(tab) / sizeof(tab[0]));

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(recherche_binaire_rec(tab, 0, n, 1) == 0);
    CHECK(recherche_binaire_rec(tab, 0, n, 7) == 3);
    CHECK(recherche_binaire_rec(tab, 0, n, 11) == 5);
    CHECK(recherche_binaire_rec(tab, 0, n, 6) == -1);
    CHECK(recherche_binaire_rec(tab, 3, 3, 5) == -1);   /* intervalle vide */
    OK("recherche binaire recursive");
    return 0;
}
