#include <stdlib.h>
#include <string.h>
#include "clings.h"

typedef struct {
    const char *nom;
    int         age;
} Personne;

static int cmp_age(const void *a, const void *b)
{
    const Personne *pa = a;
    const Personne *pb = b;
    if (pa->age < pb->age) return -1;
    return pa->age > pb->age;
}

int main(void)
{
    Personne gens[] = {
        {"Ada",   36},
        {"Linus", 21},
        {"Grace", 85},
        {"Ken",   42},
    };
    size_t n = sizeof(gens) / sizeof(gens[0]);

    qsort(gens, n, sizeof(gens[0]), cmp_age);

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
