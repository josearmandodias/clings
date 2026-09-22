/* Implémentation fournie : ne pas modifier.
 *
 * Ce fichier est compilé en même temps que modules2.c, comme un second
 * fichier source. Il a besoin du header pour rester cohérent avec les
 * déclarations. */

#include <stddef.h>
#include "modules2_table.h"

int max_tableau(const int *tab, size_t n)
{
    int max = tab[0];

    for (size_t i = 1; i < n; i++) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    return max;
}

long somme_tableau(const int *tab, size_t n)
{
    long somme = 0;

    for (size_t i = 0; i < n; i++) {
        somme += tab[i];
    }
    return somme;
}
