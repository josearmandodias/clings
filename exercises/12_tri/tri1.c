// Le tri par insertion construit une partie triée au début du tableau : pour
// chaque nouvel élément, on le fait remonter à sa place en décalant les plus
// grands vers la droite.
//
// Complexité O(n^2) dans le pire cas, mais simple et efficace sur de petits
// tableaux. Écris `tri_insertion` (avec des boucles).


// I AM NOT DONE

#include "clings.h"

void tri_insertion(int *tab, size_t n)
{
    /* TODO */
    (void)tab;
    (void)n;
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
    int a[] = {5, 2, 9, 1, 5, 6};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {4, 4, 2, 2, 4};
    int d[] = {7};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    tri_insertion(a, sizeof(a) / sizeof(a[0]));
    CHECK(est_trie(a, sizeof(a) / sizeof(a[0])));
    CHECK(a[0] == 1 && a[5] == 9);

    tri_insertion(b, sizeof(b) / sizeof(b[0]));
    CHECK(est_trie(b, sizeof(b) / sizeof(b[0])));

    tri_insertion(c, sizeof(c) / sizeof(c[0]));
    CHECK(est_trie(c, sizeof(c) / sizeof(c[0])));

    tri_insertion(d, sizeof(d) / sizeof(d[0]));
    CHECK(d[0] == 7);

    tri_insertion(NULL, 0);   /* ne doit rien faire */
    OK("tri par insertion");
    return 0;
}
