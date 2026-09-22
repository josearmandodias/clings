// Le préprocesseur ne comprend rien au C : il fait du remplacement de texte,
// avant la compilation. D'où le grand classique :
//
//   #define CARRE(x) x * x
//   CARRE(1 + 2)   ->   1 + 2 * 1 + 2   ->   5
//
// Corrige la macro CARRE (parenthèses), et remplace MAX par une version
// qui n'évalue pas ses arguments deux fois — ou plus simplement par une
// fonction, ce qui est presque toujours le bon choix en C moderne.


// I AM NOT DONE

#include "clings.h"

#define CARRE(x) x * x

static int appels = 0;

static int suivant(void)
{
    appels++;
    return 10;
}

int max(int a, int b)
{
    /* TODO */
    (void)a;
    (void)b;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(CARRE(3) == 9);
    CHECK(CARRE(1 + 2) == 9);
    CHECK(CARRE(2) * 2 == 8);
    CHECK(CARRE(0) == 0);
    CHECK(CARRE(-3) == 9);        /* un negatif au carre est positif */
    CHECK(CARRE(2 + 3) == 25);

    CHECK(max(3, 7) == 7);
    CHECK(max(-1, -5) == -1);
    CHECK(max(4, 4) == 4);        /* arguments egaux */
    CHECK(max(0, -1) == 0);
    CHECK(max(suivant(), 4) == 10);
    CHECK(appels == 1);            /* l'argument n'a ete evalue qu'une fois */
    OK("macros et evaluation");
    return 0;
}
