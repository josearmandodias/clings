// Le tri rapide choisit un pivot, partitionne le tableau autour de lui
// (plus petits à gauche, plus grands à droite), puis trie chaque côté
// récursivement.
//
// La partition de Lomuto prend le dernier élément comme pivot. Écris
// `tri_rapide` en t'appuyant sur une fonction de partition récursive.


// I AM NOT DONE

#include "clings.h"

void tri_rapide(int *tab, size_t n)
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
    int a[] = {8, 3, 1, 7, 0, 10, 2};
    int b[] = {1, 2, 3, 4, 5, 6};
    int c[] = {5, 5, 3, 3, 5, 3};
    int d[] = {42};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    tri_rapide(a, sizeof(a) / sizeof(a[0]));
    CHECK(est_trie(a, sizeof(a) / sizeof(a[0])));
    CHECK(a[0] == 0 && a[6] == 10);

    tri_rapide(b, sizeof(b) / sizeof(b[0]));
    CHECK(est_trie(b, sizeof(b) / sizeof(b[0])));

    tri_rapide(c, sizeof(c) / sizeof(c[0]));
    CHECK(est_trie(c, sizeof(c) / sizeof(c[0])));

    tri_rapide(d, sizeof(d) / sizeof(d[0]));
    CHECK(d[0] == 42);

    tri_rapide(NULL, 0);
    OK("tri rapide");
    return 0;
}
