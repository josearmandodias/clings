// `strlcat` ajoute `src` a la fin de `dst` en respectant la taille du tampon :
// elle n'ecrit jamais au-dela de `taille` octets (terminateur compris) et
// garantit un '\0' final. Sa valeur de retour est la longueur que la chaine
// AURAIT eue si le tampon avait ete assez grand : strlen(dst) + strlen(src),
// meme en cas de troncature.
//
// Cas particulier : si `taille == 0`, renvoie strlen(src) sans rien lire de
// `dst`. Complete `ma_strlcat`.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

size_t ma_strlcat(char *dst, const char *src, size_t taille)
{
    /* TODO */
    (void)dst;
    (void)src;
    (void)taille;
    return 0;
}

int main(void)
{
    char buf[16];
    char petit[10];
    char vide[8] = "abc";

    strcpy(buf, "Bonjour");
    size_t r1 = ma_strlcat(buf, " monde", sizeof buf);

    strcpy(petit, "abc");
    size_t r2 = ma_strlcat(petit, "defghij", sizeof petit);

    size_t r3 = ma_strlcat(vide, "xyz", 0);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(r1 == 13);                             /* 7 + 6 */
    CHECK(strcmp(buf, "Bonjour monde") == 0);

    CHECK(r2 == 10);                             /* 3 + 7, tronque a 9 */
    CHECK(strlen(petit) == 9);
    CHECK(strcmp(petit, "abcdefghi") == 0);
    CHECK(petit[9] == '\0');

    CHECK(r3 == 3);                              /* taille nulle : strlen(src) */
    CHECK(strcmp(vide, "abc") == 0);             /* dst non modifie */

    OK("concatenation bornee");
    return 0;
}
