#include "clings.h"

int main(void)
{
    int  x = 10;
    int *p = &x;

    *p = 42;

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
