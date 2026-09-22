#include <string.h>
#include "clings.h"

void afficher_binaire(unsigned x, char *sortie, size_t taille)
{
    if (taille == 0) return;

    size_t n = taille - 1;
    if (n > 32) n = 32;

    for (size_t i = 0; i < n; i++) {
        unsigned bit = (x >> (31u - (unsigned)i)) & 1u;
        sortie[i] = bit ? '1' : '0';
    }
    sortie[n] = '\0';
}

int main(void)
{
    char buf[33] = {0};

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
