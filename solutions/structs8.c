#include <stdlib.h>
#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

static int cmp_personne(const void *a, const void *b)
{
    const Personne *pa = a;
    const Personne *pb = b;

    if (pa->age != pb->age) {
        return pa->age < pb->age ? -1 : 1;
    }
    return strcmp(pa->nom, pb->nom);
}

int main(void)
{
    Personne gens[] = {
        {"Zoe", 20},
        {"Ada", 20},
        {"Ken", 18},
        {"Bea", 25},
    };
    size_t n = sizeof(gens) / sizeof(gens[0]);

    qsort(gens, n, sizeof(gens[0]), cmp_personne);

    CHECK(strcmp(gens[0].nom, "Ken") == 0);
    CHECK(strcmp(gens[1].nom, "Ada") == 0);
    CHECK(strcmp(gens[2].nom, "Zoe") == 0);
    CHECK(strcmp(gens[3].nom, "Bea") == 0);
    CHECK(n == 4);
    OK("qsort a deux cles");
    return 0;
}
