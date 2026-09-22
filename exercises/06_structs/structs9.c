// Une struct peut ranger un pointeur de fonction a cote de ses donnees : c'est
// ainsi que l'on represente une operation (une sorte de petit objet).
//
// `evaluer` doit appeler la fonction rangee dans le champ `calcul`, en lui
// passant `a` et `b`. Le champ `op` decrit l'operation, mais c'est bien le
// pointeur de fonction qui fait le travail.


// I AM NOT DONE

#include "clings.h"

typedef struct {
    char op;
    int (*calcul)(int, int);
} Operation;

int evaluer(const Operation *o, int a, int b)
{
    /* TODO */
    (void)o;
    (void)a;
    (void)b;
    return 0;
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
