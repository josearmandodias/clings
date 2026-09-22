#include "clings.h"

size_t index_max(const int *tab, size_t n)
{
    size_t best = 0;
    for (size_t i = 1; i < n; i++) {
        if (tab[i] > tab[best]) {
            best = i;
        }
    }
    return best;
}

int main(void)
{
    int t1[] = {3, 9, 2, 9};
    int t2[] = {5};
    int t3[] = {7, 1, 7, 2};

    CHECK(index_max(t1, 4) == 1);   /* premier 9 */
    CHECK(index_max(t2, 1) == 0);
    CHECK(index_max(t3, 4) == 0);   /* l'egalite garde le premier */
    OK("indice du premier maximum");
    return 0;
}
