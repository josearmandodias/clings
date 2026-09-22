#include "clings.h"

unsigned set_bit(unsigned x, int pos)
{
    return x | (1u << pos);
}

unsigned clear_bit(unsigned x, int pos)
{
    return x & ~(1u << pos);
}

unsigned toggle_bit(unsigned x, int pos)
{
    return x ^ (1u << pos);
}

int test_bit(unsigned x, int pos)
{
    return (int)((x >> pos) & 1u);
}

int main(void)
{
    CHECK(set_bit(0u, 3) == 8u);
    CHECK(clear_bit(0xFFu, 3) == 0xF7u);
    CHECK(toggle_bit(0xF0u, 0) == 0xF1u);
    CHECK(test_bit(8u, 3) == 1);
    CHECK(test_bit(8u, 2) == 0);

    CHECK(set_bit(set_bit(0u, 0), 1) == 3u);
    CHECK(clear_bit(0xFFFFu, 15) == 0x7FFFu);
    CHECK(toggle_bit(0x0Fu, 1) == 0x0Du);
    CHECK(test_bit(0xFFFFFFFFu, 31) == 1);

    OK("set / clear / toggle / test");
    return 0;
}
