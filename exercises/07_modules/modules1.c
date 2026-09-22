// Un programme C se compile fichier par fichier. Chaque .c est traduit
// isolément, sans rien savoir des autres : le seul moyen de lui apprendre
// qu'une fonction existe ailleurs est de lui en donner la DÉCLARATION,
// via un .h.
//
// Ici, `modules1_math.c` contient les définitions. Le header
// `modules1_math.h` est incomplet — c'est lui que tu dois corriger.
// Ouvre les deux fichiers du dossier 07_modules.
//
// (clings compile automatiquement tous les fichiers `modules1_*.c` du dossier.)


// I AM NOT DONE

#include "modules1_math.h"
#include "clings.h"

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(carre(5) == 25);
    CHECK(cube(3) == 27);

    CHECK(carre(0) == 0);
    CHECK(carre(-2) == 4);
    CHECK(cube(1) == 1);
    CHECK(cube(-2) == -8);

    CHECK(compteur_appels() == 6);
    OK("compilation separee");
    return 0;
}
