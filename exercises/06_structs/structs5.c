// Une struct peut en contenir une autre : `Cercle` a un `Point` comme centre.
// On accede aux champs imbriques avec deux niveaux : c->centre.x.
//
// `contient` renvoie vrai si le point `p` tombe dans le disque : la distance
// au carre doit rester <= rayon au carre. Pas besoin de racine carree.
//
// Compare des carres d'int : sur les valeurs de test, aucun debordement.


// I AM NOT DONE

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
    /* TODO */
    (void)c;
    (void)p;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    Cercle c = {.centre = {.x = 0, .y = 0}, .rayon = 5};

    CHECK(contient(&c, (Point){3, 4}) == 1);
    CHECK(contient(&c, (Point){4, 4}) == 0);
    CHECK(contient(&c, (Point){5, 0}) == 1);
    CHECK(contient(&c, (Point){0, -5}) == 1);
    OK("struct imbriquee");
    return 0;
}
