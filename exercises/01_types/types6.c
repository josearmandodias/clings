// Convertir un `double` en `int` TRONQUE vers zéro : 2.7 devient 2, et
// -2.4 devient -2. Pour arrondir à l'entier le plus proche, il faut le faire
// soi-même (ou appeler une fonction adaptée).
//
// `arrondi` doit donner l'entier le plus proche ; en cas de demi exact, on
// s'éloigne de zéro (2.5 -> 3 et -2.5 -> -3).


// I AM NOT DONE

#include "clings.h"

int arrondi(double x)
{
    return x;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(arrondi(2.7) == 3);
    CHECK(arrondi(2.4) == 2);
    CHECK(arrondi(2.5) == 3);
    CHECK(arrondi(-2.5) == -3);
    CHECK(arrondi(-2.4) == -2);
    OK("arrondi");
    return 0;
}
