// Le produit matriciel n'est qu'une accumulation : c[i][j] est la somme des
// a[i][k] * b[k][j] pour tous les k. Trois boucles imbriquees, et rien
// d'autre. La dimension commune vaut ici 3.
//
// `multiplier` doit ecrire dans `c` (2x2) le produit de `a` (2x3) par
// `b` (3x2). Complete-la.


// I AM NOT DONE

#include "clings.h"

void multiplier(int c[2][2], const int a[2][3], const int b[3][2])
{
    /* TODO */
    (void)c;
    (void)a;
    (void)b;
}

int main(void)
{
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    int b[3][2] = {
        {7,  8},
        {9, 10},
        {11, 12},
    };
    int c[2][2] = {{0, 0}, {0, 0}};

    multiplier(c, a, b);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(c[0][0] == 58);    /* 1*7 + 2*9  + 3*11 */
    CHECK(c[0][1] == 64);    /* 1*8 + 2*10 + 3*12 */
    CHECK(c[1][0] == 139);   /* 4*7 + 5*9  + 6*11 */
    CHECK(c[1][1] == 154);   /* 4*8 + 5*10 + 6*12 */
    OK("produit de matrices");
    return 0;
}
