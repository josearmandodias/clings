#include "clings.h"

int compte_bits(unsigned x)
{
    int n = 0;
    while (x) {
        x &= x - 1u;
        n++;
    }
    return n;
}

int main(void)
{
    CHECK(compte_bits(0u) == 0);
    CHECK(compte_bits(1u) == 1);
    CHECK(compte_bits(0xFFu) == 8);
    CHECK(compte_bits(0x80000000u) == 1);
    CHECK(compte_bits(0xFFFFFFFFu) == 32);
    CHECK(compte_bits(0x0000000Fu) == 4);
    CHECK(compte_bits(0xAAAAAAAAu) == 16);

    OK("population count");
    return 0;
}
