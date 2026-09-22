// Comparer deux `double` avec `==` est presque toujours une erreur : en
// binaire, 0.1 + 0.2 ne vaut pas exactement 0.3. Il faut tolérer un petit
// écart.
//
// `presque_egaux` renvoie 1 si `|a - b| < 1e-9`, 0 sinon.
// Utilise `fabs` de <math.h>.


// I AM NOT DONE

#include <math.h>
#include "clings.h"

int presque_egaux(double a, double b)
{
    return a == b;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(presque_egaux(0.1 + 0.2, 0.3) == 1);
    CHECK(presque_egaux(1.0, 1.0) == 1);
    CHECK(presque_egaux(1.0, 1.1) == 0);
    OK("comparaison flottante");
    return 0;
}
