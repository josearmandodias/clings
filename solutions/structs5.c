#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point centre;
    int   rayon;
} Cercle;

int contient(const Cercle *c, Point p)
{
    int dx = p.x - c->centre.x;
    int dy = p.y - c->centre.y;
    return dx * dx + dy * dy <= c->rayon * c->rayon;
}

int main(void)
{
    Cercle c = {.centre = {.x = 0, .y = 0}, .rayon = 5};

    CHECK(contient(&c, (Point){3, 4}) == 1);
    CHECK(contient(&c, (Point){4, 4}) == 0);
    CHECK(contient(&c, (Point){5, 0}) == 1);
    CHECK(contient(&c, (Point){0, -5}) == 1);
    OK("struct imbriquee");
    return 0;
}
