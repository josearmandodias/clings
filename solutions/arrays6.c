#include "clings.h"

static void inverser_plage(int *tab, size_t debut, size_t fin)
{
    while (debut < fin) {
        int tmp = tab[debut];
        tab[debut] = tab[fin];
        tab[fin] = tmp;
        debut++;
        fin--;
    }
}

void rotation_gauche(int *tab, size_t n, size_t k)
{
    if (n == 0) {
        return;
    }
    k %= n;
    if (k == 0) {
        return;
    }
    inverser_plage(tab, 0, k - 1);
    inverser_plage(tab, k, n - 1);
    inverser_plage(tab, 0, n - 1);
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 3, 4, 5};
    int d[] = {9};

    rotation_gauche(a, 5, 2);
    rotation_gauche(b, 5, 0);
    rotation_gauche(c, 5, 7);   /* 7 % 5 == 2 */
    rotation_gauche(d, 0, 3);

    CHECK(a[0] == 3 && a[1] == 4 && a[2] == 5 && a[3] == 1 && a[4] == 2);

    CHECK(b[0] == 1 && b[1] == 2 && b[2] == 3 && b[3] == 4 && b[4] == 5);

    CHECK(c[0] == 3 && c[1] == 4 && c[2] == 5 && c[3] == 1 && c[4] == 2);

    CHECK(d[0] == 9);
    OK("rotation a gauche");
    return 0;
}
