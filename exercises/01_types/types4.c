// Un `int` fait 32 bits : au-delà de INT_MAX, l'addition « déborde ».
// Or le débordement d'un entier SIGNÉ est un comportement indéfini en C :
// le compilateur a le droit de supposer qu'il n'arrive jamais, et UBSan le
// signale à l'exécution.
//
// `somme_large` doit renvoyer la vraie somme, même quand elle dépasse INT_MAX.
// Change le type de l'opération, pas celui des paramètres.


// I AM NOT DONE

#include <limits.h>
#include "clings.h"

long somme_large(int a, int b)
{
    return a + b;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(somme_large(INT_MAX, 1) == (long)INT_MAX + 1);
    CHECK(somme_large(-5, 2) == -3);
    CHECK(somme_large(INT_MIN, -1) == (long)INT_MIN - 1);
    OK("addition sans débordement");
    return 0;
}
