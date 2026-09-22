#include "clings.h"

unsigned long factorielle(unsigned n)
{
    if (n <= 1) {
        return 1;
    }
    return n * factorielle(n - 1);
}

int main(void)
{
    CHECK(factorielle(0) == 1);
    CHECK(factorielle(1) == 1);
    CHECK(factorielle(5) == 120);
    CHECK(factorielle(10) == 3628800);
    OK("factorielle recursive");
    return 0;
}
