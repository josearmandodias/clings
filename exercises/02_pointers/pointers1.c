// Un pointeur est une variable qui contient une adresse.
//   &x   -> l'adresse de x
//   *p   -> la valeur rangée à l'adresse p  (déréférencement)
//
// Complète les deux lignes marquées TODO.


// I AM NOT DONE

#include "clings.h"

int main(void)
{
    int  x = 10;
    int *p = /* TODO: fais pointer p sur x */;

    /* TODO: en passant par p, mets x à 42 */;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(x == 42);
    CHECK(*p == 42);
    CHECK(p == &x);
    CHECK(p != NULL);

    x = 7;                  /* ecrire par la variable... */
    CHECK(*p == 7);         /* ...se voit a travers p */
    *p = 42;                /* et l'inverse aussi */
    CHECK(x == 42);
    OK("lire et ecrire a travers un pointeur");
    return 0;
}
