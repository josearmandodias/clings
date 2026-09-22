#include <stdio.h>
#include <string.h>
#include "clings.h"

int saluer(char *dst, size_t taille, const char *nom)
{
    int n = snprintf(dst, taille, "Bonjour %s", nom);
    return (n >= 0 && (size_t)n < taille);
}

int main(void)
{
    char buf[16];

    CHECK(saluer(buf, sizeof(buf), "Ada") == 1);
    CHECK(strcmp(buf, "Bonjour Ada") == 0);

    CHECK(saluer(buf, sizeof(buf), "Grace Hopper") == 0);   /* trop long */
    CHECK(strlen(buf) == 15);                               /* tronque, pas de debordement */

    char pile[12];                                          /* taille exacte : 11 + '\0' */
    CHECK(saluer(pile, sizeof(pile), "Ada") == 1);
    CHECK(strcmp(pile, "Bonjour Ada") == 0);

    char court[8];                                          /* une case de moins que necessaire */
    CHECK(saluer(court, sizeof(court), "Ada") == 0);
    CHECK(strlen(court) == 7);

    CHECK(saluer(buf, 0, "Ada") == 0);                      /* taille nulle : rien ecrit */

    CHECK(saluer(buf, sizeof(buf), "") == 1);               /* nom vide */
    CHECK(strcmp(buf, "Bonjour ") == 0);
    OK("ecriture bornee dans un tampon");
    return 0;
}
