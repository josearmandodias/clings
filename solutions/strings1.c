#include <string.h>
#include "clings.h"

int main(void)
{
    char mot[4];

    mot[0] = 'o';
    mot[1] = 'u';
    mot[2] = 'i';
    mot[3] = '\0';

    CHECK(sizeof mot >= sizeof("oui"));   /* de la place pour le '\0' */
    CHECK(strlen(mot) == 3);
    CHECK(strcmp(mot, "oui") == 0);
    CHECK(mot[3] == '\0');        /* le terminateur est bien au 4e octet */
    OK("une chaine se termine par un octet nul");
    return 0;
}
