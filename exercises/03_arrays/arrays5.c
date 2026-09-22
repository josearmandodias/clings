// Inverser un tableau "en place", c'est echanger le premier avec le dernier,
// le deuxieme avec l'avant-dernier, etc., jusqu'a se rejoindre au milieu.
// Une seule variable temporaire suffit ; aucun tableau annexe n'est necessaire.
//
// `inverser` doit renverser les `n` elements de `tab`. Complete-la.


// I AM NOT DONE

#include "clings.h"

void inverser(int *tab, size_t n)
{
    /* TODO */
    if (n >= 2) {
        int tmp = tab[0];
        tab[0] = tab[n - 1];
        tab[n - 1] = tmp;
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

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(a[0] == 4 && a[1] == 3 && a[2] == 2 && a[3] == 1);

    CHECK(b[0] == 5 && b[1] == 4 && b[2] == 3 && b[3] == 2 && b[4] == 1);

    CHECK(c[0] == 42);
    CHECK(d[0] == 1 && d[1] == 2);
    OK("inversion en place");
    return 0;
}
