// Une struct est un agrégat de champs, sans méthode, sans constructeur.
// Elle se copie entièrement à l'affectation et au passage par valeur.
//
// Déclare le type Point, puis complète les initialisations.
// Utilise la syntaxe des initialisateurs désignés : {.x = 1, .y = 2}.


// I AM NOT DONE

#include "clings.h"

/* TODO: definis ici un type `Point` avec deux champs int x et y */

int main(void)
{
    Point a = /* TODO: x = 3, y = 4 */;
    Point b = a;              /* copie complete, pas une reference */

    b.x = 99;

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
