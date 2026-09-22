// Le boutisme (endianness) est l'ordre des octets en memoire. Inverser les
// octets d'un entier 32 bits echange poids fort et poids faible : chacun des
// quatre octets doit se retrouver a la position miroir.
//
// Complete `swap32`. Exemple : 0x11223344 devient 0x44332211.


// I AM NOT DONE

#include "clings.h"

unsigned swap32(unsigned x)
{
    /* TODO */
    (void)x;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(swap32(0x11223344u) == 0x44332211u);
    CHECK(swap32(swap32(0x12345678u)) == 0x12345678u);   /* involutif */
    CHECK(swap32(0u) == 0u);
    CHECK(swap32(0xFFFFFFFFu) == 0xFFFFFFFFu);
    CHECK(swap32(0x000000FFu) == 0xFF000000u);
    CHECK(swap32(0xAABBCCDDu) == 0xDDCCBBAAu);

    OK("inversion des octets");
    return 0;
}
