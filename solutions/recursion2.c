#include "clings.h"

long puissance(long base, unsigned exp)
{
    if (exp == 0) {
        return 1;
    }
    long demi = puissance(base, exp / 2);
    if (exp % 2 == 0) {
        return demi * demi;
    }
    return demi * demi * base;
}

int main(void)
{
    CHECK(puissance(2, 10) == 1024);
    CHECK(puissance(3, 0) == 1);
    CHECK(puissance(5, 3) == 125);
    CHECK(puissance(2, 0) == 1);
    OK("exponentiation rapide");
    return 0;
}
