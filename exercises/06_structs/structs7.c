// Une union superpose ses membres dans le meme espace : elle ne peut en
// contenir qu'un seul a la fois. Pour savoir lequel est valide, on l'accompagne
// d'une etiquette (ici l'enum `Type`) : c'est l'union etiquetee.
//
// `en_double` lit la bonne variante selon `n->type` et la convertit en double.


// I AM NOT DONE

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
    /* TODO */
    (void)n;
    return 0.0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    Nombre a = {.type = ENTIER, .valeur.i = 42};
    Nombre b = {.type = REEL, .valeur.d = 2.5};

    CHECK(en_double(&a) == 42.0);
    CHECK(en_double(&b) == 2.5);
    OK("enum et union etiquetee");
    return 0;
}
