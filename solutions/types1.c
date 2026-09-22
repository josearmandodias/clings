#include "clings.h"

int main(void)
{
    int    petit  = 42;
    long   grand  = 4200000000L;
    size_t taille = sizeof(long);
    double ratio  = 0.5;

    printf("  petit  = %d\n", petit);
    printf("  grand  = %ld\n", grand);
    printf("  taille = %zu\n", taille);
    printf("  ratio  = %f\n", ratio);

    CHECK(petit == 42);
    CHECK(grand == 4200000000L);
    CHECK(taille == sizeof(long));
    CHECK(ratio == 0.5);
    OK("les formats correspondent aux types");
    return 0;
}
