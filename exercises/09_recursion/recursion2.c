// L'exponentiation rapide (« par élévation au carré ») calcule base^exp en
// O(log exp) au lieu de O(exp) :
//
//   exp paire   : base^exp = (base^(exp/2))^2
//   exp impaire : base^exp = (base^(exp/2))^2 * base
//
// Écris `puissance` récursivement, sans boucle.


// I AM NOT DONE

#include "clings.h"

long puissance(long base, unsigned exp)
{
    /* TODO */
    (void)base;
    (void)exp;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(puissance(2, 10) == 1024);
    CHECK(puissance(3, 0) == 1);
    CHECK(puissance(5, 3) == 125);
    CHECK(puissance(2, 0) == 1);
    OK("exponentiation rapide");
    return 0;
}
