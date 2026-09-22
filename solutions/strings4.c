#include <ctype.h>
#include <string.h>
#include "clings.h"

void majuscule_premiere(char *s)
{
    if (s && *s) {
        *s = (char)toupper((unsigned char)*s);
    }
}

int main(void)
{
    char mot[] = "bonjour";

    majuscule_premiere(mot);

    CHECK(strcmp(mot, "Bonjour") == 0);

    char vide[] = "";
    majuscule_premiere(vide);           /* chaine vide : inoffensif */
    CHECK(vide[0] == '\0');

    majuscule_premiere(NULL);           /* s peut valoir NULL */

    char haut[] = "Zoo";
    majuscule_premiere(haut);
    CHECK(strcmp(haut, "Zoo") == 0);    /* deja une majuscule */

    char symbole[] = "!oui";
    majuscule_premiere(symbole);
    CHECK(strcmp(symbole, "!oui") == 0);/* toupper ne touche pas '!' */
    OK("litteral en lecture seule vs tableau modifiable");
    return 0;
}
