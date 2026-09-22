#include "clings.h"

const int *chercher(const int *tab, size_t n, int valeur)
{
    for (size_t i = 0; i < n; i++)
        if (tab[i] == valeur)
            return &tab[i];
    return NULL;
}

int main(void)
{
    const int tab[] = {4, 8, 15, 16, 23, 42};

    CHECK(chercher(tab, 6, 15) == &tab[2]);
    CHECK(chercher(tab, 6, 100) == NULL);
    CHECK(chercher(tab, 0, 4) == NULL);
    OK("retour de pointeur");
    return 0;
}
