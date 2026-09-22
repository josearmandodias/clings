// Parcourir un tableau pour en extraire une information est le geste de base.
// Ici on cherche l'INDICE du plus grand element, et non sa valeur.
//
// En cas d'egalite, on garde la PREMIERE occurrence : on ne remplace donc le
// candidat que lorsqu'on trouve STRICTEMENT plus grand.
//
// `index_max` doit renvoyer l'indice du premier maximum (`n >= 1`).


// I AM NOT DONE

#include "clings.h"

size_t index_max(const int *tab, size_t n)
{
    /* TODO */
    (void)tab;
    (void)n;
    return 0;
}

int main(void)
{
    int t1[] = {3, 9, 2, 9};
    int t2[] = {5};
    int t3[] = {7, 1, 7, 2};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(index_max(t1, 4) == 1);   /* premier 9 */
    CHECK(index_max(t2, 1) == 0);
    CHECK(index_max(t3, 4) == 0);   /* l'egalite garde le premier */
    OK("indice du premier maximum");
    return 0;
}
