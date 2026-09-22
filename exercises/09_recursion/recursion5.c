// Somme des chiffres d'un entier, de façon récursive :
//   somme(n) = (n % 10) + somme(n / 10), avec somme(0) = 0.
//
// Les nombres négatifs sont d'abord ramenés à leur valeur absolue :
// somme_chiffres(-123) doit valoir 6.
//
// Écris `somme_chiffres` récursivement.


// I AM NOT DONE

#include "clings.h"

int somme_chiffres(long n)
{
    /* TODO */
    (void)n;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(somme_chiffres(0) == 0);
    CHECK(somme_chiffres(5) == 5);
    CHECK(somme_chiffres(123) == 6);
    CHECK(somme_chiffres(9999) == 36);
    CHECK(somme_chiffres(-123) == 6);
    OK("somme des chiffres recursive");
    return 0;
}
