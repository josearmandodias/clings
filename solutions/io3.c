#include <stdio.h>
#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

int sauver_point(const char *chemin, const Point *p)
{
    FILE *f = fopen(chemin, "wb");
    if (!f) return -1;

    size_t n = fwrite(p, sizeof *p, 1, f);
    if (fclose(f) != 0) return -1;

    return n == 1 ? 0 : -1;
}

int charger_point(const char *chemin, Point *p)
{
    FILE *f = fopen(chemin, "rb");
    if (!f) return -1;

    size_t n = fread(p, sizeof *p, 1, f);
    fclose(f);

    return n == 1 ? 0 : -1;
}

int main(void)
{
    const char *tmp = "clings_io3.tmp";
    Point p = {.x = 3, .y = -7};
    Point q = {.x = 0, .y = 0};

    CHECK(sauver_point(tmp, &p) == 0);
    CHECK(charger_point(tmp, &q) == 0);
    CHECK(q.x == 3 && q.y == -7);

    CHECK(charger_point("/aucun/fichier/ici", &q) == -1);

    remove(tmp);
    OK("fichier binaire");
    return 0;
}
