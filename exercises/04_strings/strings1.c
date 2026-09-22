// Une "chaîne" en C, c'est juste un tableau de char qui se termine par un
// octet nul '\0'. Toutes les fonctions de <string.h> cherchent ce '\0'.
// S'il manque, elles continuent à lire au-delà du tableau.
//
// Ici le tableau est trop petit d'un octet : il n'y a pas la place pour le
// terminateur. Corrige la taille, puis remplis correctement le tableau.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

int main(void)
{
    char mot[3];

    mot[0] = 'o';
    mot[1] = 'u';
    mot[2] = 'i';

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strlen(mot) == 3);
    CHECK(strcmp(mot, "oui") == 0);
    CHECK(mot[3] == '\0');        /* le terminateur est bien au 4e octet */
    OK("une chaine se termine par un octet nul");
    return 0;
}
