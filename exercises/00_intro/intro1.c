// Bienvenue dans clings.
//
// Le principe : chaque fichier contient un petit programme cassé ou incomplet.
// Ton travail est de le faire compiler ET passer ses tests.
//
// Trois règles :
//   1. Tu ne modifies jamais ce qui est sous la ligne "NE TOUCHE PAS".
//   2. Tout compile avec -Wall -Wextra -Werror : un warning = une erreur.
//      C'est volontaire. En C, les warnings sont presque toujours des bugs.
//      pour débloquer le suivant.
//
// Celui-ci fonctionne déjà. Retire simplement la ligne ci-dessous et sauvegarde.


// I AM NOT DONE

#include "clings.h"

int main(void)
{
    OK("premier exercice");
    CHECK(1 + 1 == 2);
    return 0;
}
