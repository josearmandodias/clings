// Compter les bits a 1 (population count) revient a retirer un bit a 1 a
// chaque tour de boucle. L'astuce `x &= x - 1` efface le bit a 1 le plus bas.
//
// Complete `compte_bits` : renvoie le nombre de bits a 1 de `x`.


// I AM NOT DONE

#include "clings.h"

int compte_bits(unsigned x)
{
    /* TODO */
    (void)x;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
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
