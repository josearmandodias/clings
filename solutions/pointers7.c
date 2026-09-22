#include <string.h>
#include "clings.h"

size_t longueur_totale(const char *const *mots, size_t n)
{
    size_t total = 0;
    for (size_t i = 0; i < n; i++)
        total += strlen(mots[i]);
    return total;
}

int main(void)
{
    static const char *const mots[] = {"un", "deux", "trois"};

    CHECK(longueur_totale(mots, 3) == 11);
    CHECK(longueur_totale(mots, 0) == 0);
    OK("const à plusieurs niveaux");
    return 0;
}
