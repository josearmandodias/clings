// strtol(s, &fin, 10) convertit le début de `s` en long et range dans `fin`
// l'adresse du premier caractère NON consommé. Elle saute les espaces, accepte
// un signe, puis lit des chiffres. Si aucun chiffre n'est lu, `fin` reste
// égal à `s`.
//
// `extraire_entier` renvoie 0 si au moins un chiffre a été lu (et écrit la
// valeur dans `*valeur`), -1 sinon. Dans tous les cas, `*suffixe` pointe sur
// le premier caractère non consommé : il n'est jamais NULL.


// I AM NOT DONE

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "clings.h"

int extraire_entier(const char *s, long *valeur, const char **suffixe)
{
    /* TODO */
    (void)s;
    (void)valeur;
    (void)suffixe;
    return -1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    long v = 0;
    const char *fin = NULL;

    CHECK(extraire_entier("42", &v, &fin) == 0);
    CHECK(v == 42 && strcmp(fin, "") == 0);

    CHECK(extraire_entier("12abc", &v, &fin) == 0);
    CHECK(v == 12 && strcmp(fin, "abc") == 0);

    CHECK(extraire_entier("   -7xyz", &v, &fin) == 0);
    CHECK(v == -7 && strcmp(fin, "xyz") == 0);

    CHECK(extraire_entier("abc", &v, &fin) == -1);

    OK("strtol et endptr");
    return 0;
}
