#include "clings.h"

int arrondi(double x)
{
    return x < 0.0 ? (int)(x - 0.5) : (int)(x + 0.5);
}

int main(void)
{
    CHECK(arrondi(2.7) == 3);
    CHECK(arrondi(2.4) == 2);
    CHECK(arrondi(2.5) == 3);
    CHECK(arrondi(-2.5) == -3);
    CHECK(arrondi(-2.4) == -2);
    OK("arrondi");
    return 0;
}
