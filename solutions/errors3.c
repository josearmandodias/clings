#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "clings.h"

int extraire_entier(const char *s, long *valeur, const char **suffixe)
{
    char *fin = NULL;
    long v = strtol(s, &fin, 10);

    if (suffixe) *suffixe = fin;
    if (fin == s) return -1;

    if (valeur) *valeur = v;
    return 0;
}

int main(void)
{
    long v = 0;
    const char *fin = NULL;

    CHECK(extraire_entier("42", &v, &fin) == 0);
    CHECK(v == 42 && strcmp(fin, "") == 0);

    CHECK(extraire_entier("12abc", &v, &fin) == 0);
    CHECK(v == 12 && strcmp(fin, "abc") == 0);

    CHECK(extraire_entier("   -7xyz", &v, &fin) == 0);
    CHECK(v == -7 && strcmp(fin, "xyz") == 0);

    CHECK(extraire_entier("abc", &v, &fin) == -1);

    OK("strtol et endptr");
    return 0;
}
