// L'ordre des champs change la taille d'une struct. Le processeur aligne
// chaque champ sur un multiple de sa taille et comble les trous par du
// remplissage (padding).
//
// Avec `char a; int b; char c;` : le `int` doit etre aligne sur 4 octets,
// donc 3 octets de trou apres `a`, et 3 autres apres `c` -> 12 octets.
//
// Reordonne les trois champs (memes noms, memes types) pour que
// `sizeof(Melange)` tombe a 8. Ne touche pas aux tests.


// I AM NOT DONE

#include "clings.h"

typedef struct {
    char a;
    int  b;
    char c;
} Melange;

int main(void)
{
    Melange m = {.a = 1, .b = 2, .c = 3};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(sizeof(Melange) == 8);
    CHECK(m.a == 1);
    CHECK(m.b == 2);
    CHECK(m.c == 3);
    OK("ordre des champs et padding");
    return 0;
}
