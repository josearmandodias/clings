// Un pointeur de pointeur permet à une fonction de rendre une adresse à
// l'appelant : elle écrit dans `*out`. C'est la façon idiomatique de
// « renvoyer » une allocation sans la confondre avec un échec.
//
// `creer_int` alloue un `int`, y écrit `valeur`, range l'adresse dans `*out`
// et renvoie 1. Si `out == NULL`, ou si l'allocation échoue, renvoie 0.
//
// (clings compte les allocations : CHECK_NO_LEAK échoue s'il en reste.)


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

int creer_int(int **out, int valeur)
{
    *out = NULL;
    (void)valeur;
    return 0;
}

int main(void)
{
    int *p = NULL;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(creer_int(&p, 7) == 1);
    CHECK(p != NULL && *p == 7);
    free(p);

    CHECK(creer_int(NULL, 7) == 0);

    CHECK_NO_LEAK();
    OK("allocation via un pointeur de pointeur");
    return 0;
}
