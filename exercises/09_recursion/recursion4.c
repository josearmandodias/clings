// Tours de Hanoï : déplacer n disques d'une tige vers une autre, via une
// tige intermédiaire, sans jamais poser un grand disque sur un plus petit.
//
// Déplacer n disques, c'est déplacer n-1 disques sur la tige `via`, bouger le
// plus grand disque (un coup), puis ramener les n-1 disques sur `vers`.
// `hanoi` incrémente `*coups` à chaque déplacement. Pour n disques : 2^n - 1.


// I AM NOT DONE

#include "clings.h"

void hanoi(int n, char de, char vers, char via, long *coups)
{
    /* TODO */
    (void)n;
    (void)de;
    (void)vers;
    (void)via;
    (void)coups;
}

int main(void)
{
    long coups = 0;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    hanoi(0, 'A', 'C', 'B', &coups);
    CHECK(coups == 0);

    coups = 0;
    hanoi(3, 'A', 'C', 'B', &coups);
    CHECK(coups == 7);

    coups = 0;
    hanoi(5, 'A', 'C', 'B', &coups);
    CHECK(coups == 31);
    OK("tours de Hanoi");
    return 0;
}
