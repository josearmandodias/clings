#include "clings.h"

int somme(const int *tab, size_t n)
{
    int total = 0;
    for (size_t i = 0; i < n; i++) {
        total += tab[i];
    }
    return total;
}

int main(void)
{
    int valeurs[] = {1, 2, 3, 4, 5};

    CHECK(sizeof(valeurs) / sizeof(valeurs[0]) == 5);   /* ici, ca marche */
    CHECK(somme(valeurs, 5) == 15);

    int un[] = {7};
    CHECK(somme(un, 1) == 7);          /* un seul element */
    CHECK(somme(un, 0) == 0);          /* rien a sommer */
    OK("un tableau se passe toujours avec sa longueur");
    return 0;
}
