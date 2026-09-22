// Une recherche lineaire dans un tableau de structs : on compare le champ
// `nom` de chaque element avec celui cherche.
//
// `trouver` renvoie l'index de la premiere Personne dont le nom correspond,
// ou -1 si aucune ne correspond (et -1 aussi si n vaut 0).
//
// `strcmp(a, b) == 0` teste l'egalite de deux chaines.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

int trouver(const Personne *gens, size_t n, const char *nom)
{
    /* TODO */
    (void)gens;
    (void)n;
    (void)nom;
    return -1;
}

int main(void)
{
    Personne gens[] = {
        {"Ada",   36},
        {"Linus", 21},
        {"Grace", 85},
    };

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(trouver(gens, 3, "Linus") == 1);
    CHECK(trouver(gens, 3, "Grace") == 2);
    CHECK(trouver(gens, 3, "Ada") == 0);
    CHECK(trouver(gens, 3, "Ken") == -1);
    CHECK(trouver(gens, 0, "Ada") == -1);
    OK("tableau de structs et recherche");
    return 0;
}
