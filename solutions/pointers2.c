#include "clings.h"

void echange(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int x = 1, y = 2;

    echange(&x, &y);

    CHECK(x == 2);
    CHECK(y == 1);

    echange(&x, &y);          /* un second echange revient a l'etat initial */
    CHECK(x == 1 && y == 2);

    echange(&x, &x);          /* se permuter avec soi-meme reste inoffensif */
    CHECK(x == 1);
    OK("passage par adresse");
    return 0;
}
