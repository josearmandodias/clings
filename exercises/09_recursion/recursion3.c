// L'algorithme d'Euclide repose sur : pgcd(a, b) = pgcd(b, a % b), et
// pgcd(a, 0) = a. Écris-le de façon récursive.
//
// Pour accepter les négatifs, calcule d'abord sur les valeurs absolues :
// pgcd(-12, 18) doit valoir 6.


// I AM NOT DONE

#include "clings.h"

int pgcd(int a, int b)
{
    /* TODO */
    (void)a;
    (void)b;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(pgcd(12, 18) == 6);
    CHECK(pgcd(17, 5) == 1);
    CHECK(pgcd(0, 5) == 5);
    CHECK(pgcd(-12, 18) == 6);
    OK("pgcd recursif");
    return 0;
}
