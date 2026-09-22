#define CLINGS_TRACK_ALLOC
#include <stdint.h>
#include "clings.h"

int *tableau_zeros(size_t n)
{
    if (n == 0 || n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    return calloc(n, sizeof(int));
}

int main(void)
{
    int *t = tableau_zeros(4);
    CHECK(t != NULL);
    for (int i = 0; i < 4; i++) {
        CHECK(t[i] == 0);
    }
    free(t);

    CHECK(tableau_zeros(0) == NULL);
    CHECK(tableau_zeros(SIZE_MAX / sizeof(int) + 1) == NULL);
    CHECK_NO_LEAK();
    OK("calloc et garde anti-debordement");
    return 0;
}
