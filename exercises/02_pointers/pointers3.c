// Le C n'a pas de type Option/Result. Le patron idiomatique est :
// la fonction renvoie un code de succès, et écrit son résultat dans un
// paramètre de sortie.
//
// Complète `parse_positif` : elle renvoie 1 et écrit la valeur dans *out si la
// chaîne est un entier > 0, sinon elle renvoie 0 et ne touche pas à *out.
// Attention : `out` peut valoir NULL, il faut le gérer.


// I AM NOT DONE

#include <stdlib.h>
#include "clings.h"

int parse_positif(const char *s, int *out)
{
    int v = atoi(s);
    /* TODO */
    return 0;
}

int main(void)
{
    int v = -999;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(parse_positif("12", &v) == 1);
    CHECK(v == 12);

    CHECK(parse_positif("0", &v) == 0);
    CHECK(v == 12);                    /* v ne doit pas avoir bouge */

    CHECK(parse_positif("-3", &v) == 0);
    CHECK(v == 12);

    CHECK(parse_positif("7", NULL) == 1);   /* ne doit pas planter */

    CHECK(parse_positif("+5", &v) == 1);
    CHECK(v == 5);

    CHECK(parse_positif("  8", &v) == 1);   /* atoi saute les blancs */
    CHECK(v == 8);

    CHECK(parse_positif("-3", NULL) == 0);  /* echec et out NULL : pas de plantage */
    OK("parametre de sortie et NULL");
    return 0;
}
