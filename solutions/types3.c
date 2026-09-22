#include "clings.h"

double moyenne(int somme, int n)
{
    return (double)somme / n;
}

int main(void)
{
    CHECK(moyenne(7, 2) == 3.5);
    CHECK(moyenne(10, 4) == 2.5);
    CHECK(moyenne(9, 3) == 3.0);
    CHECK(moyenne(1, 1) == 1.0);
    CHECK(moyenne(-7, 2) == -3.5);
    OK("division flottante");
    return 0;
}
