// L'opérateur `##` colle deux jetons en un seul, pendant le préprocesseur :
//
//   #define CONCAT(a, b) a##b
//   CONCAT(2, 3)               ->   23
//   CONCAT(mon_petit_, test)   ->   mon_petit_test
//
// La macro `CONCAT` ci-dessous est fausse : corrige-la pour que les deux
// CHECK passent. Le deuxième colle un préfixe et le nom d'une fonction.


// I AM NOT DONE

#include "clings.h"

#define CONCAT(a, b) a b

// ---------------------------- NE TOUCHE PAS -----------------------------

static int mon_petit_test(void)
{
    return 42;
}

int main(void)
{
    CHECK(CONCAT(2, 3) == 23);
    CHECK(CONCAT(mon_petit_, test)() == 42);
    OK("collage de jetons");
    return 0;
}
