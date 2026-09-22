// Un `enum` donne des noms aux petites valeurs entières. Associé à un
// `switch`, il permet de traiter chaque cas explicitement — et le compilateur
// vérifie avec -Wswitch que tu n'en as oublié aucun.
//
// `nom_saison` doit renvoyer le nom de la saison :
//   PRINTEMPS -> "printemps", ETE -> "ete", AUTOMNE -> "automne",
//   HIVER -> "hiver".
// Écris un `switch` qui couvre les quatre cas.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

typedef enum { PRINTEMPS, ETE, AUTOMNE, HIVER } Saison;

const char *nom_saison(Saison s)
{
    (void)s;
    return "";
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(nom_saison(PRINTEMPS), "printemps") == 0);
    CHECK(strcmp(nom_saison(ETE), "ete") == 0);
    CHECK(strcmp(nom_saison(AUTOMNE), "automne") == 0);
    CHECK(strcmp(nom_saison(HIVER), "hiver") == 0);
    OK("enum et switch");
    return 0;
}
