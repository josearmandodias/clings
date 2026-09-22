#include "clings.h"

int recherche_binaire(const int *tab, size_t n, int cible)
{
    size_t debut = 0;
    size_t fin = n;

    while (debut < fin) {
        size_t milieu = debut + (fin - debut) / 2;
        if (tab[milieu] == cible) {
            return (int)milieu;
        } else if (tab[milieu] < cible) {
            debut = milieu + 1;
        } else {
            fin = milieu;
        }
    }
    return -1;
}

int main(void)
{
    int t[] = {1, 3, 5, 7, 9, 11};

    CHECK(recherche_binaire(t, 6, 7) == 3);
    CHECK(recherche_binaire(t, 6, 1) == 0);
    CHECK(recherche_binaire(t, 6, 11) == 5);
    CHECK(recherche_binaire(t, 6, 4) == -1);
    CHECK(recherche_binaire(t, 1, 1) == 0);
    CHECK(recherche_binaire(t, 0, 7) == -1);
    OK("recherche binaire");
    return 0;
}
