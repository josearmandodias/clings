// Le tri par fusion coupe le tableau en deux, trie chaque moitié
// récursivement, puis fusionne les deux moitiés triées.
//
// Il a besoin d'un tampon temporaire de la même taille que le tableau :
// alloue-le une seule fois avant de commencer, et libère-le à la fin.
// C'est un tri stable, en O(n log n).


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <stdlib.h>
#include "clings.h"

void tri_fusion(int *tab, size_t n)
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
    int a[] = {9, 3, 7, 1, 8, 2};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {4, 4, 2, 2, 4};
    int d[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    tri_fusion(a, sizeof(a) / sizeof(a[0]));
    CHECK(est_trie(a, sizeof(a) / sizeof(a[0])));
    CHECK(a[0] == 1 && a[5] == 9);

    tri_fusion(b, sizeof(b) / sizeof(b[0]));
    CHECK(est_trie(b, sizeof(b) / sizeof(b[0])));

    tri_fusion(c, sizeof(c) / sizeof(c[0]));
    CHECK(est_trie(c, sizeof(c) / sizeof(c[0])));

    tri_fusion(d, sizeof(d) / sizeof(d[0]));
    CHECK(est_trie(d, sizeof(d) / sizeof(d[0])));
    CHECK(d[0] == 1 && d[11] == 12);

    tri_fusion(NULL, 0);
    CHECK_NO_LEAK();
    OK("tri par fusion");
    return 0;
}
