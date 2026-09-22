#include "clings.h"

#define LIRE   1u
#define ECRIRE 2u
#define EXEC   4u

int a_permission(unsigned perms, unsigned flag)
{
    return (perms & flag) != 0;
}

unsigned ajouter(unsigned perms, unsigned flag)
{
    return perms | flag;
}

unsigned retirer(unsigned perms, unsigned flag)
{
    return perms & ~flag;
}

int main(void)
{
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
