// Le piège le plus classique du C : comparer un signé et un non signé.
// Dans `i < taille`, i est converti en size_t (non signé) : un i négatif
// devient un nombre gigantesque, et la boucle part dans le décor.
//
// Corrige le type de `i` pour que le compilateur soit content.


// I AM NOT DONE

#include "clings.h"

int main(void)
{
    int    valeurs[] = {10, 20, 30, 40};
    size_t taille    = sizeof(valeurs) / sizeof(valeurs[0]);
    int    somme     = 0;

    for (int i = 0; i < taille; i++) {
        somme += valeurs[i];
    }

    int    un[]     = {7};
    size_t n_un     = sizeof(un) / sizeof(un[0]);
    int    somme_un = 0;

    for (int i = 0; i < n_un; i++) {
        somme_un += un[i];
    }

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(taille == 4);
    CHECK(somme == 100);
    CHECK(n_un == 1);
    CHECK(somme_un == 7);
    OK("index et taille ont le meme type");
    return 0;
}
