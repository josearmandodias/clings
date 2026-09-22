#include "clings.h"

#define L 3
#define C 4

void transpose(const int entree[L][C], int sortie[C][L])
{
    for (size_t i = 0; i < L; i++) {
        for (size_t j = 0; j < C; j++) {
            sortie[j][i] = entree[i][j];
        }
    }
}

int main(void)
{
    int a[L][C] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12},
    };
    int t[C][L] = {{0}};

    transpose(a, t);

    CHECK(sizeof(a) == 12 * sizeof(int));
    CHECK(t[0][0] == 1);
    CHECK(t[0][2] == 9);
    CHECK(t[1][0] == 2);
    CHECK(t[2][2] == 11);
    CHECK(t[3][1] == 8);
    CHECK(t[3][2] == 12);
    OK("tableaux a deux dimensions");
    return 0;
}
