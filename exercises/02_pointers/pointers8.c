// Une fonction peut recevoir une AUTRE fonction en paramètre via un pointeur
// de fonction : `int (*f)(int)` est « un pointeur vers une fonction qui prend
// un int et renvoie un int ».
//
// `somme_appliquee` applique `f` à chaque élément, puis additionne les
// résultats. Par exemple avec `carre`, {1,2,3} donne 1 + 4 + 9 = 14.
// N'oublie pas le cas `n == 0`.


// I AM NOT DONE

#include "clings.h"

int somme_appliquee(const int *tab, size_t n, int (*f)(int))
{
    (void)tab;
    (void)n;
    (void)f;
    return 0;
}

static int carre(int x)
{
    return x * x;
}

static int oppose(int x)
{
    return -x;
}

int main(void)
{
    const int tab[] = {1, 2, 3};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(somme_appliquee(tab, 3, carre) == 14);
    CHECK(somme_appliquee(tab, 3, oppose) == -6);
    CHECK(somme_appliquee(tab, 0, carre) == 0);
    OK("pointeur de fonction");
    return 0;
}
