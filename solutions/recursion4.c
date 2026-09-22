#include "clings.h"

void hanoi(int n, char de, char vers, char via, long *coups)
{
    if (n <= 0) {
        return;
    }
    hanoi(n - 1, de, via, vers, coups);
    (*coups)++;
    hanoi(n - 1, via, vers, de, coups);
}

int main(void)
{
    long coups = 0;

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
