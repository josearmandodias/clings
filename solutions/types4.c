#include <limits.h>
#include "clings.h"

long somme_large(int a, int b)
{
    return (long)a + b;
}

int main(void)
{
    CHECK(somme_large(INT_MAX, 1) == (long)INT_MAX + 1);
    CHECK(somme_large(-5, 2) == -3);
    CHECK(somme_large(INT_MIN, -1) == (long)INT_MIN - 1);
    OK("addition sans débordement");
    return 0;
}
