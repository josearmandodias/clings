#include "clings.h"

int main(void)
{
    int    valeurs[] = {10, 20, 30, 40};
    size_t taille    = sizeof(valeurs) / sizeof(valeurs[0]);
    int    somme     = 0;

    for (size_t i = 0; i < taille; i++) {
        somme += valeurs[i];
    }

    int    un[]     = {7};
    size_t n_un     = sizeof(un) / sizeof(un[0]);
    int    somme_un = 0;

    for (size_t i = 0; i < n_un; i++) {
        somme_un += un[i];
    }

    CHECK(taille == 4);
    CHECK(somme == 100);
    CHECK(n_un == 1);
    CHECK(somme_un == 7);
    OK("index et taille ont le meme type");
    return 0;
}
