#include "clings.h"

typedef struct {
    char op;
    int (*calcul)(int, int);
} Operation;

int evaluer(const Operation *o, int a, int b)
{
    return o->calcul(a, b);
}

// ---------------------------- NE TOUCHE PAS -----------------------------
static int addition(int a, int b)
{
    return a + b;
}

static int multiplication(int a, int b)
{
    return a * b;
}

int main(void)
{
    Operation plus = {'+', addition};
    Operation fois = {'*', multiplication};

    CHECK(evaluer(&plus, 2, 3) == 5);
    CHECK(evaluer(&fois, 2, 3) == 6);
    OK("pointeur de fonction dans une struct");
    return 0;
}
