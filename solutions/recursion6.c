#include "clings.h"

int recherche_binaire_rec(const int *tab, int debut, int fin, int cible)
{
    if (debut >= fin) {
        return -1;
    }
    int milieu = debut + (fin - debut) / 2;
    if (tab[milieu] == cible) {
        return milieu;
    }
    if (tab[milieu] < cible) {
        return recherche_binaire_rec(tab, milieu + 1, fin, cible);
    }
    return recherche_binaire_rec(tab, debut, milieu, cible);
}

int main(void)
{
    int tab[] = {1, 3, 5, 7, 9, 11};
    int n = (int)(sizeof(tab) / sizeof(tab[0]));

    CHECK(recherche_binaire_rec(tab, 0, n, 1) == 0);
    CHECK(recherche_binaire_rec(tab, 0, n, 7) == 3);
    CHECK(recherche_binaire_rec(tab, 0, n, 11) == 5);
    CHECK(recherche_binaire_rec(tab, 0, n, 6) == -1);
    CHECK(recherche_binaire_rec(tab, 3, 3, 5) == -1);   /* intervalle vide */
    OK("recherche binaire recursive");
    return 0;
}
