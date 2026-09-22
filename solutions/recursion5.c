#include "clings.h"

int somme_chiffres(long n)
{
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        return 0;
    }
    return (int)(n % 10) + somme_chiffres(n / 10);
}

int main(void)
{
    CHECK(somme_chiffres(0) == 0);
    CHECK(somme_chiffres(5) == 5);
    CHECK(somme_chiffres(123) == 6);
    CHECK(somme_chiffres(9999) == 36);
    CHECK(somme_chiffres(-123) == 6);
    OK("somme des chiffres recursive");
    return 0;
}
