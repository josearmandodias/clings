#define CLINGS_TRACK_ALLOC
#include <stdlib.h>
#include "clings.h"

void tri_comptage(int *tab, size_t n, int max)
{
    if (n == 0) {
        return;
    }
    int *compte = calloc((size_t)max + 1, sizeof *compte);
    if (compte == NULL) {
        return;
    }
    for (size_t i = 0; i < n; i++) {
        compte[tab[i]]++;
    }
    size_t k = 0;
    for (int v = 0; v <= max; v++) {
        while (compte[v] > 0) {
            tab[k++] = v;
            compte[v]--;
        }
    }
    free(compte);
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
