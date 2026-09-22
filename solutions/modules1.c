#include "modules1_math.h"
#include "clings.h"

int main(void)
{
    CHECK(carre(5) == 25);
    CHECK(cube(3) == 27);

    CHECK(carre(0) == 0);
    CHECK(carre(-2) == 4);
    CHECK(cube(1) == 1);
    CHECK(cube(-2) == -8);

    CHECK(compteur_appels() == 6);
    OK("compilation separee");
    return 0;
}
