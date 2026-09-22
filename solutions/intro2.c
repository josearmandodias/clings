#include <stdio.h>
#include "clings.h"

int main(void)
{
    int a = 19;
    int b = 23;
    int somme = a + b;
    double moyenne = somme / 2.0;

    printf("somme = %d, moyenne = %.1f\n", somme, moyenne);

    CHECK(somme == 42);
    OK("message de compilation lu");
    return 0;
}
