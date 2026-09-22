// Passer une struct par valeur la copie. Pour la modifier — ou juste pour
// éviter la copie sur une grosse structure — on passe un pointeur, et on
// accède aux champs avec `->` (qui est du sucre pour (*p).champ).
//
// `deplacer` doit modifier le point de l'appelant.
// `norme_carree` ne doit pas le modifier : passe-la en const.


// I AM NOT DONE

#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

void deplacer(Point p, int dx, int dy)
{
    p.x += dx;
    p.y += dy;
}

int norme_carree(Point p)
{
    return p.x * p.x + p.y * p.y;
}

int main(void)
{
    Point p = {.x = 1, .y = 2};

    deplacer(&p, 2, 2);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(p.x == 3 && p.y == 4);
    CHECK(norme_carree(&p) == 25);

    deplacer(&p, 0, 0);                  /* deplacement nul : rien ne change */
    CHECK(p.x == 3 && p.y == 4);

    Point origine = {.x = 0, .y = 0};
    CHECK(norme_carree(&origine) == 0);  /* le carre d'un negatif est positif */

    Point negatif = {.x = -3, .y = 4};
    CHECK(norme_carree(&negatif) == 25);
    OK("modifier une struct via un pointeur");
    return 0;
}
