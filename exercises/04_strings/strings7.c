// Un "mot" est ici une suite maximale de caracteres qui ne sont pas des
// blancs (`isspace`). Compter les mots revient donc a detecter chaque
// transition blanc -> non-blanc.
//
// `compter_mots` renvoie le nombre de mots de `s`. Complete-la.


// I AM NOT DONE

#include <ctype.h>
#include "clings.h"

size_t compter_mots(const char *s)
{
    /* TODO */
    (void)s;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(compter_mots("") == 0);
    CHECK(compter_mots("   ") == 0);
    CHECK(compter_mots("un deux trois") == 3);
    CHECK(compter_mots("  un   deux ") == 2);
    CHECK(compter_mots("mot") == 1);
    OK("compter les mots");
    return 0;
}
