// Afficher un entier en binaire aide a verifier visuellement les masques.
// On ecrit les 32 bits du poids fort au poids faible, puis le '\0' final
// (il faut donc une zone d'au moins 33 octets).
//
// Complete `afficher_binaire`. `taille` est la taille de `sortie`.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

void afficher_binaire(unsigned x, char *sortie, size_t taille)
{
    /* TODO */
    (void)x;
    (void)sortie;
    (void)taille;
}

int main(void)
{
    char buf[33] = {0};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    afficher_binaire(0u, buf, sizeof buf);
    CHECK(strcmp(buf, "00000000000000000000000000000000") == 0);

    afficher_binaire(1u, buf, sizeof buf);
    CHECK(strcmp(buf, "00000000000000000000000000000001") == 0);

    afficher_binaire(0x80000000u, buf, sizeof buf);
    CHECK(strcmp(buf, "10000000000000000000000000000000") == 0);

    afficher_binaire(0xFFFFFFFFu, buf, sizeof buf);
    CHECK(strcmp(buf, "11111111111111111111111111111111") == 0);

    afficher_binaire(0x0000000Fu, buf, sizeof buf);
    CHECK(strcmp(buf, "00000000000000000000000000001111") == 0);

    OK("affichage binaire");
    return 0;
}
