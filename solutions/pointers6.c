#define CLINGS_TRACK_ALLOC
#include "clings.h"

int creer_int(int **out, int valeur)
{
    if (out == NULL) return 0;

    int *p = malloc(sizeof *p);
    if (p == NULL) return 0;

    *p = valeur;
    *out = p;
    return 1;
}

int main(void)
{
    int *p = NULL;

    CHECK(creer_int(&p, 7) == 1);
    CHECK(p != NULL && *p == 7);
    free(p);

    CHECK(creer_int(NULL, 7) == 0);

    CHECK_NO_LEAK();
    OK("allocation via un pointeur de pointeur");
    return 0;
}
