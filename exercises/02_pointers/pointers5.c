// Un tableau passé à une fonction « devient » un pointeur vers son premier
// élément. On peut donc le parcourir en faisant avancer le pointeur, sans
// aucun indice.
//
// `somme` additionne les `n` éléments en avançant le pointeur `tab`
// (pas d'écriture `tab[i]`). Renvoie 0 quand `n == 0`.


// I AM NOT DONE

#include "clings.h"

int somme(const int *tab, size_t n)
{
    (void)tab;
    (void)n;
    return 0;
}

int main(void)
{
    const int tab[] = {1, 2, 3, 4};
    const int seul[] = {42};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(somme(tab, 4) == 10);
    CHECK(somme(seul, 1) == 42);
    CHECK(somme(tab, 0) == 0);
    OK("arithmétique de pointeurs");
    return 0;
}
