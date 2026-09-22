#include "clings.h"

int pgcd(int a, int b)
{
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (b == 0) {
        return a;
    }
    return pgcd(b, a % b);
}

int main(void)
{
    CHECK(pgcd(12, 18) == 6);
    CHECK(pgcd(17, 5) == 1);
    CHECK(pgcd(0, 5) == 5);
    CHECK(pgcd(-12, 18) == 6);
    OK("pgcd recursif");
    return 0;
}
