// La division entière tronque. `7 / 2` vaut 3, pas 3.5, même si tu ranges le
// résultat dans un double : la conversion a lieu APRÈS la division.
//
// Corrige `moyenne()` pour qu'elle renvoie la vraie moyenne.


// I AM NOT DONE

#include "clings.h"

double moyenne(int somme, int n)
{
    return somme / n;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(moyenne(7, 2) == 3.5);
    CHECK(moyenne(10, 4) == 2.5);
    CHECK(moyenne(9, 3) == 3.0);
    CHECK(moyenne(1, 1) == 1.0);
    CHECK(moyenne(-7, 2) == -3.5);
    OK("division flottante");
    return 0;
}
