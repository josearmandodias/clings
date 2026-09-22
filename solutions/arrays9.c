#include <string.h>
#include "clings.h"

void supprimer(int *tab, size_t *n, size_t pos)
{
    memmove(tab + pos, tab + pos + 1, (*n - pos - 1) * sizeof *tab);
    (*n)--;
}

int main(void)
{
    int t1[] = {10, 20, 30, 40, 50};
    size_t n1 = 5;
    int t2[] = {1, 2, 3};
    size_t n2 = 3;
    int t3[] = {7, 8, 9};
    size_t n3 = 3;

    supprimer(t1, &n1, 1);   /* au milieu */
    supprimer(t2, &n2, 0);   /* en tete */
    supprimer(t3, &n3, 2);   /* en queue */

    CHECK(n1 == 4);
    CHECK(t1[0] == 10 && t1[1] == 30 && t1[2] == 40 && t1[3] == 50);

    CHECK(n2 == 2);
    CHECK(t2[0] == 2 && t2[1] == 3);

    CHECK(n3 == 2);
    CHECK(t3[0] == 7 && t3[1] == 8);
    OK("suppression avec recouvrement");
    return 0;
}
