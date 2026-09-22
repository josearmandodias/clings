#include "clings.h"

int somme_appliquee(const int *tab, size_t n, int (*f)(int))
{
    int total = 0;
    for (size_t i = 0; i < n; i++)
        total += f(tab[i]);
    return total;
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

    CHECK(somme_appliquee(tab, 3, carre) == 14);
    CHECK(somme_appliquee(tab, 3, oppose) == -6);
    CHECK(somme_appliquee(tab, 0, carre) == 0);
    OK("pointeur de fonction");
    return 0;
}
