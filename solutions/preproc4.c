#include <stdio.h>
#include <string.h>
#include "clings.h"

#define NIVEAU 2

const char *nom_niveau(void)
{
#ifdef DEBUG
    fprintf(stderr, "NIVEAU = %d\n", NIVEAU);
#endif

#if NIVEAU == 1
    return "debutant";
#elif NIVEAU == 2
    return "intermediaire";
#else
    return "expert";
#endif
}

int main(void)
{
    CHECK(strcmp(nom_niveau(), "intermediaire") == 0);
    OK("compilation conditionnelle");
    return 0;
}
