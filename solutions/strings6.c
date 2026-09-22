#include <string.h>
#include "clings.h"

size_t ma_strlcat(char *dst, const char *src, size_t taille)
{
    size_t dl = 0;
    while (dl < taille && dst[dl] != '\0') {
        dl++;
    }

    size_t sl = strlen(src);
    size_t total = dl + sl;

    if (dl < taille) {
        size_t place = taille - dl - 1;
        size_t i = 0;
        while (i < place && src[i] != '\0') {
            dst[dl + i] = src[i];
            i++;
        }
        dst[dl + i] = '\0';
    }
    return total;
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
