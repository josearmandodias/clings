#include <stdlib.h>
#include "clings.h"

int parse_positif(const char *s, int *out)
{
    int v = atoi(s);
    if (v <= 0) return 0;
    if (out) *out = v;
    return 1;
}

int main(void)
{
    int v = -999;

    CHECK(parse_positif("12", &v) == 1);
    CHECK(v == 12);

    CHECK(parse_positif("0", &v) == 0);
    CHECK(v == 12);                    /* v ne doit pas avoir bouge */

    CHECK(parse_positif("-3", &v) == 0);
    CHECK(v == 12);

    CHECK(parse_positif("7", NULL) == 1);   /* ne doit pas planter */

    CHECK(parse_positif("+5", &v) == 1);
    CHECK(v == 5);

    CHECK(parse_positif("  8", &v) == 1);   /* atoi saute les blancs */
    CHECK(v == 8);

    CHECK(parse_positif("-3", NULL) == 0);  /* echec et out NULL : pas de plantage */
    OK("parametre de sortie et NULL");
    return 0;
}
