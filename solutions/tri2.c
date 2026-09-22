#define CLINGS_TRACK_ALLOC
#include <stdlib.h>
#include "clings.h"

static void fusion(int *tab, int *tmp, size_t debut, size_t milieu, size_t fin)
{
    size_t i = debut;
    size_t j = milieu;
    size_t k = debut;

    while (i < milieu && j < fin) {
        if (tab[i] <= tab[j]) {
            tmp[k++] = tab[i++];
        } else {
            tmp[k++] = tab[j++];
        }
    }
    while (i < milieu) {
        tmp[k++] = tab[i++];
    }
    while (j < fin) {
        tmp[k++] = tab[j++];
    }
    for (i = debut; i < fin; i++) {
        tab[i] = tmp[i];
    }
}

static void trier(int *tab, int *tmp, size_t debut, size_t fin)
{
    if (fin - debut <= 1) {
        return;
    }
    size_t milieu = debut + (fin - debut) / 2;
    trier(tab, tmp, debut, milieu);
    trier(tab, tmp, milieu, fin);
    fusion(tab, tmp, debut, milieu, fin);
}

void tri_fusion(int *tab, size_t n)
{
    if (n < 2) {
        return;
    }
    int *tmp = malloc(n * sizeof *tmp);
    if (tmp == NULL) {
        return;
    }
    trier(tab, tmp, 0, n);
    free(tmp);
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
