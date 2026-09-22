#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

int main(void)
{
    Point a = {.x = 3, .y = 4};
    Point b = a;

    b.x = 99;

    CHECK(a.x == 3 && a.y == 4);
    CHECK(b.x == 99 && b.y == 4);
    CHECK(sizeof(Point) == 2 * sizeof(int));

    Point c = {.x = -1, .y = -2};        /* valeurs negatives */
    CHECK(c.x == -1 && c.y == -2);

    Point d = {.x = 0, .y = 0};          /* origine */
    CHECK(d.x == 0 && d.y == 0);
    OK("une struct se copie");
    return 0;
}
