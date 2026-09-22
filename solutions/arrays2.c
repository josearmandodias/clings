#include "clings.h"

#define N 10

int main(void)
{
    int tab[N];

    for (int i = 0; i < N; i++) {
        tab[i] = i * i;
    }

    CHECK(tab[0] == 0);
    CHECK(tab[1] == 1);
    CHECK(tab[5] == 25);
    CHECK(tab[N - 1] == 81);           /* dernier indice valide : N - 1 */
    OK("pas de depassement de tableau");
    return 0;
}
