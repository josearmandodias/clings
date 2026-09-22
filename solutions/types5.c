#include "clings.h"

int modulo_positif(int a, int n)
{
    int r = a % n;
    return r < 0 ? r + n : r;
}

int main(void)
{
    CHECK(modulo_positif(-7, 3) == 2);
    CHECK(modulo_positif(7, 3) == 1);
    CHECK(modulo_positif(-1, 5) == 4);
    CHECK(modulo_positif(0, 4) == 0);
    CHECK(modulo_positif(-4, 4) == 0);
    OK("modulo positif");
    return 0;
}
