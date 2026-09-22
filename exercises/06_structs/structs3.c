// Les pointeurs de fonction sont la façon dont le C fait du polymorphisme.
// qsort() ne sait rien de tes données : tu lui passes la taille d'un élément
// et une fonction de comparaison.
//
// Signature attendue : int cmp(const void *a, const void *b)
//   < 0 si a avant b, 0 si equivalents, > 0 si a apres b.
//
// Écris `cmp_age` pour trier par âge croissant, puis appelle qsort.
// Piège : renvoyer `a - b` sur des int peut déborder ; compare plutôt.


// I AM NOT DONE

#include <stdlib.h>
#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

/* TODO: ecris cmp_age ici */

int main(void)
{
    Personne gens[] = {
        {"Ada",   36},
        {"Linus", 21},
        {"Grace", 85},
        {"Ken",   42},
    };
    size_t n = sizeof(gens) / sizeof(gens[0]);

    /* TODO: trie `gens` par age croissant avec qsort */

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(gens[0].nom, "Linus") == 0);
    CHECK(strcmp(gens[1].nom, "Ada") == 0);
    CHECK(strcmp(gens[2].nom, "Ken") == 0);
    CHECK(strcmp(gens[3].nom, "Grace") == 0);
    CHECK(n == 4);

    Personne tries[] = {{"A", 10}, {"B", 20}, {"C", 30}};
    qsort(tries, 3, sizeof(tries[0]), cmp_age);       /* deja trie */
    CHECK(tries[0].age == 10 && tries[2].age == 30);

    Personne exaequo[] = {{"X", 5}, {"Y", 3}, {"Z", 5}};
    qsort(exaequo, 3, sizeof(exaequo[0]), cmp_age);   /* ages egaux */
    CHECK(exaequo[0].age == 3);
    CHECK(exaequo[1].age == 5 && exaequo[2].age == 5);

    Personne seul[] = {{"Solo", 7}};
    qsort(seul, 1, sizeof(seul[0]), cmp_age);         /* un seul element */
    CHECK(seul[0].age == 7);
    OK("qsort et pointeur de fonction");
    return 0;
}
