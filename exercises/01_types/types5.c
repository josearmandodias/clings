// L'opérateur `%` en C suit le signe du dividende : `-7 % 3` vaut -1,
// et non 2. Or on veut souvent un reste toujours positif.
//
// `modulo_positif` doit renvoyer une valeur dans `[0, n)`, pour `n > 0`.


// I AM NOT DONE

#include "clings.h"

int modulo_positif(int a, int n)
{
    return a % n;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(modulo_positif(-7, 3) == 2);
    CHECK(modulo_positif(7, 3) == 1);
    CHECK(modulo_positif(-1, 5) == 4);
    CHECK(modulo_positif(0, 4) == 0);
    CHECK(modulo_positif(-4, 4) == 0);
    OK("modulo positif");
    return 0;
}
