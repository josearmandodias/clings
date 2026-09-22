// calloc, c'est malloc plus la remise a zero, avec un avantage de taille :
// calloc(n, taille) verifie lui-meme que la multiplication ne deborde pas.
// malloc(n * taille), lui, calcule d'abord et ne voit rien venir.
//
// `tableau_zeros` doit renvoyer un tableau de `n` int valant tous 0, ou NULL
// si `n` vaut 0 ou si `n * sizeof(int)` depasserait la taille adressable.
//
// Ecris la garde AVANT de multiplier : une fois le produit deborde, il est
// deja trop tard. `SIZE_MAX` vient de <stdint.h>.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <stdint.h>
#include "clings.h"

int *tableau_zeros(size_t n)
{
    /* TODO: refuser n == 0 et le debordement, puis allouer a zero. */
    return malloc(n * sizeof(int));
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
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
