#include "clings.h"

unsigned extraire_champ(unsigned valeur, int offset, int largeur)
{
    unsigned masque = (1u << largeur) - 1u;
    return (valeur >> offset) & masque;
}

int main(void)
{
    CHECK(extraire_champ(180u, 2, 3) == 5u);
    CHECK(extraire_champ(0xFFFFFFFFu, 8, 8) == 0xFFu);
    CHECK(extraire_champ(0u, 0, 4) == 0u);
    CHECK(extraire_champ(0xF0u, 4, 4) == 0xFu);
    CHECK(extraire_champ(0x1234u, 4, 4) == 0x3u);

    OK("extraction de champ");
    return 0;
}
