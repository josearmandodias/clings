// Un tableau de pointeurs (`const char *const *`) et un retour de pointeur
// emprunté : `plus_longue` parcourt les `n` mots et renvoie l'adresse de la
// chaîne la PLUS LONGUE, sans rien copier.
//
// En cas d'égalité, garde le premier rencontré. Et si `n == 0`, renvoie
// `NULL` — il n'y a alors aucune adresse valide à rendre.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

const char *plus_longue(const char *const *mots, size_t n)
{
    (void)n;
    return mots[0];
}

int main(void)
{
    static const char *const mots[] = {"a", "longue", "xx"};
    static const char *const exaequo[] = {"aa", "bb", "c"};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(plus_longue(mots, 3), "longue") == 0);
    CHECK(strcmp(plus_longue(exaequo, 3), "aa") == 0);
    CHECK(plus_longue(mots, 0) == NULL);
    OK("mot le plus long");
    return 0;
}
