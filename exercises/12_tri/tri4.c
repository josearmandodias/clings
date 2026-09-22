// Le tri par comptage ne compare pas les éléments : il compte combien de fois
// chaque valeur apparaît, puis reconstruit le tableau dans l'ordre.
//
// Les valeurs de `tab` sont toutes comprises entre 0 et `max` (inclus).
// Alloue un tableau de compteurs avec calloc (déjà à zéro), remplis-le, puis
// réécris `tab`. N'oublie pas de libérer.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <stdlib.h>
#include "clings.h"

void tri_comptage(int *tab, size_t n, int max)
{
    /* TODO */
    (void)tab;
    (void)n;
    (void)max;
}

static int est_trie(const int *tab, size_t n)
{
    for (size_t i = 1; i < n; i++) {
        if (tab[i - 1] > tab[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int a[] = {4, 2, 0, 2, 5, 1};
    int b[] = {3, 3, 3, 3};
    int c[] = {0};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    tri_comptage(a, sizeof(a) / sizeof(a[0]), 5);
    CHECK(est_trie(a, sizeof(a) / sizeof(a[0])));
    CHECK(a[0] == 0 && a[1] == 1 && a[3] == 2 && a[5] == 5);

    tri_comptage(b, sizeof(b) / sizeof(b[0]), 3);
    CHECK(est_trie(b, sizeof(b) / sizeof(b[0])));
    CHECK(b[0] == 3 && b[3] == 3);

    tri_comptage(c, sizeof(c) / sizeof(c[0]), 0);
    CHECK(c[0] == 0);

    tri_comptage(NULL, 0, 5);
    CHECK_NO_LEAK();
    OK("tri par comptage");
    return 0;
}
