#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "clings.h"

int lire_entier(const char *s, long *out)
{
    char *fin;

    errno = 0;
    long v = strtol(s, &fin, 10);

    if (fin == s)        return -1;
    if (*fin != '\0')    return -1;
    if (errno == ERANGE) return -1;

    if (out) *out = v;
    return 0;
}

int main(void)
{
    long v = 0;

    CHECK(lire_entier("123", &v) == 0 && v == 123);
    CHECK(lire_entier("-7", &v) == 0 && v == -7);

    CHECK(lire_entier("", &v) == -1);
    CHECK(lire_entier("12abc", &v) == -1);
    CHECK(lire_entier("99999999999999999999999999", &v) == -1);

    /* errno n'est pas remis a zero tout seul : ce cas verifie qu'on l'a fait. */
    CHECK(lire_entier("0", &v) == 0 && v == 0);

    CHECK(lire_entier("   42", &v) == 0 && v == 42);   /* strtol saute les blancs */
    CHECK(lire_entier("+5", &v) == 0 && v == 5);

    v = 777;
    CHECK(lire_entier("abc", &v) == -1);
    CHECK(v == 777);                                    /* *out intact en cas d'echec */
    OK("gestion d'erreur a la C");
    return 0;
}
