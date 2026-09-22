// Les permissions se representent souvent par des drapeaux (flags) : chaque
// bit est une permission independante. Combiner des permissions, c'est
// combiner des bits avec | ; en retirer une, c'est masquer ce bit.
//
// Complete `a_permission`, `ajouter` et `retirer`.


// I AM NOT DONE

#include "clings.h"

#define LIRE   1u
#define ECRIRE 2u
#define EXEC   4u

int a_permission(unsigned perms, unsigned flag)
{
    /* TODO */
    (void)perms;
    (void)flag;
    return 0;
}

unsigned ajouter(unsigned perms, unsigned flag)
{
    /* TODO */
    (void)perms;
    (void)flag;
    return 0;
}

unsigned retirer(unsigned perms, unsigned flag)
{
    /* TODO */
    (void)perms;
    (void)flag;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(a_permission(0u, LIRE) == 0);
    CHECK(a_permission(LIRE | ECRIRE, ECRIRE) == 1);
    CHECK(a_permission(LIRE | ECRIRE, LIRE) == 1);
    CHECK(a_permission(LIRE, EXEC) == 0);

    CHECK(ajouter(0u, EXEC) == EXEC);
    CHECK(ajouter(LIRE, ECRIRE) == (LIRE | ECRIRE));
    CHECK(ajouter(LIRE | ECRIRE, ECRIRE) == (LIRE | ECRIRE));

    CHECK(retirer(LIRE | ECRIRE, LIRE) == ECRIRE);
    CHECK(retirer(LIRE, EXEC) == LIRE);
    CHECK(retirer(LIRE | ECRIRE, LIRE | ECRIRE) == 0u);

    OK("drapeaux de permissions");
    return 0;
}
