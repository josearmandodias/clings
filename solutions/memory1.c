#define CLINGS_TRACK_ALLOC
#include "clings.h"

int *fabrique(size_t n)
{
    int *tab = malloc(n * sizeof(*tab));
    if (!tab) return NULL;
    for (size_t i = 0; i < n; i++) {
        tab[i] = (int)i * 2;
    }
    return tab;
}

int main(void)
{
    int *t = fabrique(5);

    CHECK(t != NULL);
    CHECK(t[0] == 0);
    CHECK(t[4] == 8);
    free(t);

    int *u = fabrique(3);
    CHECK(u != NULL);
    CHECK(u[0] == 0 && u[2] == 4);
    free(u);

    free(NULL);                 /* liberer NULL est inoffensif */
    CHECK_NO_LEAK();
    OK("la memoire qui survit a la fonction vient du tas");
    return 0;
}
