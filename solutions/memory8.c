#define CLINGS_TRACK_ALLOC
#include "clings.h"

int *agrandir(int *tab, size_t ancien, size_t nouveau)
{
    (void)ancien;
    int *tmp = realloc(tab, nouveau * sizeof(*tmp));
    if (tmp == NULL) {
        return NULL;
    }
    return tmp;
}

int main(void)
{
    int *tab = malloc(3 * sizeof(*tab));
    CHECK(tab != NULL);
    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;

    int *plus = agrandir(tab, 3, 6);
    CHECK(plus != NULL);
    CHECK(plus[0] == 1);
    CHECK(plus[1] == 2);
    CHECK(plus[2] == 3);

    plus[3] = 10;
    plus[4] = 20;
    plus[5] = 30;
    CHECK(plus[5] == 30);

    free(plus);
    CHECK_NO_LEAK();
    OK("realloc sans perdre le bloc");
    return 0;
}
