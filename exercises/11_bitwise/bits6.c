// Extraire un champ de bits consiste a le ramener tout a droite avec un
// decalage, puis a ne garder que `largeur` bits avec un masque. Le masque de
// `largeur` bits vaut (1 << largeur) - 1.
//
// Complete `extraire_champ` : renvoie les `largeur` bits de `valeur` a partir
// de la position `offset`.


// I AM NOT DONE

#include "clings.h"

unsigned extraire_champ(unsigned valeur, int offset, int largeur)
{
    /* TODO */
    (void)valeur;
    (void)offset;
    (void)largeur;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(extraire_champ(180u, 2, 3) == 5u);
    CHECK(extraire_champ(0xFFFFFFFFu, 8, 8) == 0xFFu);
    CHECK(extraire_champ(0u, 0, 4) == 0u);
    CHECK(extraire_champ(0xF0u, 4, 4) == 0xFu);
    CHECK(extraire_champ(0x1234u, 4, 4) == 0x3u);

    OK("extraction de champ");
    return 0;
}
