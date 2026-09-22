// Manipuler un bit isole d'un entier non signe est la base de tout le
// bitwise. `pos` est le numero du bit, en partant de 0 (poids faible).
//
// Complete les quatre operations :
//   set_bit    -> met le bit a 1
//   clear_bit  -> met le bit a 0
//   toggle_bit -> inverse le bit
//   test_bit   -> renvoie 1 si le bit vaut 1, sinon 0


// I AM NOT DONE

#include "clings.h"

unsigned set_bit(unsigned x, int pos)
{
    /* TODO */
    (void)x;
    (void)pos;
    return 0;
}

unsigned clear_bit(unsigned x, int pos)
{
    /* TODO */
    (void)x;
    (void)pos;
    return 0;
}

unsigned toggle_bit(unsigned x, int pos)
{
    /* TODO */
    (void)x;
    (void)pos;
    return 0;
}

int test_bit(unsigned x, int pos)
{
    /* TODO */
    (void)x;
    (void)pos;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
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
