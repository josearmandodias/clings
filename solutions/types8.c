#include <string.h>
#include "clings.h"

typedef enum { PRINTEMPS, ETE, AUTOMNE, HIVER } Saison;

const char *nom_saison(Saison s)
{
    switch (s) {
    case PRINTEMPS: return "printemps";
    case ETE:       return "ete";
    case AUTOMNE:   return "automne";
    case HIVER:     return "hiver";
    }
    return "";
}

int main(void)
{
    CHECK(strcmp(nom_saison(PRINTEMPS), "printemps") == 0);
    CHECK(strcmp(nom_saison(ETE), "ete") == 0);
    CHECK(strcmp(nom_saison(AUTOMNE), "automne") == 0);
    CHECK(strcmp(nom_saison(HIVER), "hiver") == 0);
    OK("enum et switch");
    return 0;
}
