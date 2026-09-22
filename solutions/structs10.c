#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

int trouver(const Personne *gens, size_t n, const char *nom)
{
    for (size_t i = 0; i < n; i++) {
        if (strcmp(gens[i].nom, nom) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int main(void)
{
    Personne gens[] = {
        {"Ada",   36},
        {"Linus", 21},
        {"Grace", 85},
    };

    CHECK(trouver(gens, 3, "Linus") == 1);
    CHECK(trouver(gens, 3, "Grace") == 2);
    CHECK(trouver(gens, 3, "Ada") == 0);
    CHECK(trouver(gens, 3, "Ken") == -1);
    CHECK(trouver(gens, 0, "Ada") == -1);
    OK("tableau de structs et recherche");
    return 0;
}
