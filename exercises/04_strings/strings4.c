// `char *s = "texte";` ne copie rien : s pointe sur un littéral rangé dans
// une section en lecture seule du binaire. Écrire dedans plante à
// l'exécution (segfault), alors que ça compile sans broncher.
//
// `char s[] = "texte";` copie le littéral dans un tableau modifiable.
//
// `majuscule_premiere` doit fonctionner. Change la déclaration de `mot`
// dans main, et corrige le type du paramètre.


// I AM NOT DONE

#include <ctype.h>
#include <string.h>
#include "clings.h"

void majuscule_premiere(const char *s)
{
    if (s && *s) {
        *s = (char)toupper((unsigned char)*s);
    }
}

int main(void)
{
    char *mot = "bonjour";

    majuscule_premiere(mot);

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
