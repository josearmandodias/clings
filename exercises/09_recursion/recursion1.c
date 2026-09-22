// Une fonction récursive s'appelle elle-même sur un problème plus petit,
// jusqu'à un cas de base qu'elle sait résoudre directement.
//
// n! = n * (n-1)!, avec 0! = 1! = 1. Écris `factorielle` de façon récursive
// (elle doit s'appeler elle-même, sans boucle).


// I AM NOT DONE

#include "clings.h"

unsigned long factorielle(unsigned n)
{
    /* TODO */
    (void)n;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(factorielle(0) == 1);
    CHECK(factorielle(1) == 1);
    CHECK(factorielle(5) == 120);
    CHECK(factorielle(10) == 3628800);
    OK("factorielle recursive");
    return 0;
}
