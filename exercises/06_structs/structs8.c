// qsort trie selon une relation d'ordre totale fournie par le comparateur.
// Ici on veut trier par age croissant, puis departager les ex aequo par le nom
// (ordre alphabetique).
//
// Signature imposee : int cmp(const void *a, const void *b).
// Complete `cmp_personne`, puis appelle qsort sur `gens`.


// I AM NOT DONE

#include <stdlib.h>
#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

static int cmp_personne(const void *a, const void *b)
{
    /* TODO */
    (void)a;
    (void)b;
    return 0;
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

    /* TODO: trie `gens` avec qsort */
    (void)cmp_personne;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(gens[0].nom, "Ken") == 0);
    CHECK(strcmp(gens[1].nom, "Ada") == 0);
    CHECK(strcmp(gens[2].nom, "Zoe") == 0);
    CHECK(strcmp(gens[3].nom, "Bea") == 0);
    CHECK(n == 4);
    OK("qsort a deux cles");
    return 0;
}
