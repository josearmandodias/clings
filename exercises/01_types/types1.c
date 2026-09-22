// printf ne vérifie rien à l'exécution : c'est le compilateur qui doit t'avertir.
// Si le spécificateur ne correspond pas au type de l'argument, tu lis n'importe
// quoi. Corrige les trois appels printf pour que ça compile.
//
// Rappels : %d = int, %ld = long, %zu = size_t, %f = double, %p = void*


// I AM NOT DONE

#include "clings.h"

int main(void)
{
    int    petit  = 42;
    long   grand  = 4200000000L;
    size_t taille = sizeof(long);
    double ratio  = 0.5;

    printf("  petit  = %d\n", petit);
    printf("  grand  = %d\n", grand);
    printf("  taille = %d\n", taille);
    printf("  ratio  = %d\n", ratio);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(petit == 42);
    CHECK(grand == 4200000000L);
    CHECK(taille == sizeof(long));
    CHECK(ratio == 0.5);
    OK("les formats correspondent aux types");
    return 0;
}
