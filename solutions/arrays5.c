#include "clings.h"

void inverser(int *tab, size_t n)
{
    for (size_t i = 0; i < n / 2; i++) {
        int tmp = tab[i];
        tab[i] = tab[n - 1 - i];
        tab[n - 1 - i] = tmp;
    }
}

int main(void)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {42};
    int d[] = {1, 2};

    inverser(a, 4);
    inverser(b, 5);
    inverser(c, 1);
    inverser(d, 0);

    CHECK(a[0] == 4 && a[1] == 3 && a[2] == 2 && a[3] == 1);

    CHECK(b[0] == 5 && b[1] == 4 && b[2] == 3 && b[3] == 2 && b[4] == 1);

    CHECK(c[0] == 42);
    CHECK(d[0] == 1 && d[1] == 2);
    OK("inversion en place");
    return 0;
}
