#include "clings.h"

static void echanger(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

static size_t partition(int *tab, size_t debut, size_t fin)
{
    int pivot = tab[fin - 1];
    size_t i = debut;
    for (size_t j = debut; j + 1 < fin; j++) {
        if (tab[j] <= pivot) {
            echanger(&tab[i], &tab[j]);
            i++;
        }
    }
    echanger(&tab[i], &tab[fin - 1]);
    return i;
}

static void trier(int *tab, size_t debut, size_t fin)
{
    if (fin - debut <= 1) {
        return;
    }
    size_t p = partition(tab, debut, fin);
    trier(tab, debut, p);
    trier(tab, p + 1, fin);
}

void tri_rapide(int *tab, size_t n)
{
    if (n < 2) {
        return;
    }
    trier(tab, 0, n);
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
