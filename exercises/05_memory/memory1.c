// Pile (stack) vs tas (heap).
//
// Une variable locale vit dans la trame de pile de sa fonction. Dès que la
// fonction retourne, cette trame est réutilisée par l'appel suivant.
// Renvoyer l'adresse d'une locale te donne un pointeur qui pointe sur de la
// mémoire déjà recyclée : c'est un "dangling pointer".
//
// C'est exactement ce que le borrow checker de Rust interdit à la compilation.
// En C, tu dois y penser toi-même.
//
// Corrige `fabrique` pour que le tableau survive au retour de la fonction.
// Pense à ce que ça implique pour l'appelant.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

int *fabrique(size_t n)
{
    int tab[16];
    for (size_t i = 0; i < n; i++) {
        tab[i] = (int)i * 2;
    }
    return tab;
}

int main(void)
{
    int *t = fabrique(5);

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
