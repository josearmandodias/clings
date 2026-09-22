#include "clings.h"

int somme(const int *tab, size_t n)
{
    int total = 0;
    for (size_t i = 0; i < n; i++) {
        total += *tab;
        tab++;
    }
    return total;
}

int main(void)
{
    const int tab[] = {1, 2, 3, 4};
    const int seul[] = {42};

    CHECK(somme(tab, 4) == 10);
    CHECK(somme(seul, 1) == 42);
    CHECK(somme(tab, 0) == 0);
    OK("arithmétique de pointeurs");
    return 0;
}
