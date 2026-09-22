#include "clings.h"

void multiplier(int c[2][2], const int a[2][3], const int b[3][2])
{
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            int somme = 0;
            for (size_t k = 0; k < 3; k++) {
                somme += a[i][k] * b[k][j];
            }
            c[i][j] = somme;
        }
    }
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

    CHECK(c[0][0] == 58);    /* 1*7 + 2*9  + 3*11 */
    CHECK(c[0][1] == 64);    /* 1*8 + 2*10 + 3*12 */
    CHECK(c[1][0] == 139);   /* 4*7 + 5*9  + 6*11 */
    CHECK(c[1][1] == 154);   /* 4*8 + 5*10 + 6*12 */
    OK("produit de matrices");
    return 0;
}
