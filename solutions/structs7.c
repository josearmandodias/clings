#include "clings.h"

typedef enum {
    ENTIER,
    REEL
} Type;

typedef struct {
    Type type;
    union {
        long   i;
        double d;
    } valeur;
} Nombre;

double en_double(const Nombre *n)
{
    if (n->type == ENTIER) {
        return (double)n->valeur.i;
    }
    return n->valeur.d;
}

int main(void)
{
    Nombre a = {.type = ENTIER, .valeur.i = 42};
    Nombre b = {.type = REEL, .valeur.d = 2.5};

    CHECK(en_double(&a) == 42.0);
    CHECK(en_double(&b) == 2.5);
    OK("enum et union etiquetee");
    return 0;
}
