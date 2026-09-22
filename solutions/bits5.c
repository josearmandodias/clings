#include "clings.h"

unsigned swap32(unsigned x)
{
    return (x >> 24)
         | ((x >> 8)  & 0x0000FF00u)
         | ((x << 8)  & 0x00FF0000u)
         |  (x << 24);
}

int main(void)
{
    CHECK(swap32(0x11223344u) == 0x44332211u);
    CHECK(swap32(swap32(0x12345678u)) == 0x12345678u);   /* involutif */
    CHECK(swap32(0u) == 0u);
    CHECK(swap32(0xFFFFFFFFu) == 0xFFFFFFFFu);
    CHECK(swap32(0x000000FFu) == 0xFF000000u);
    CHECK(swap32(0xAABBCCDDu) == 0xDDCCBBAAu);

    OK("inversion des octets");
    return 0;
}
