// `void *` efface le type : une fonction peut manipuler n'importe quelle zone
// mémoire, à condition de connaître sa TAILLE en octets.
//
// `echanger` échange le contenu de deux zones de `taille` octets. On peut
// procéder octet par octet avec des `unsigned char *`, ou via `memcpy` et un
// tampon temporaire.
//
// Cette même fonction servira pour des `int` comme pour des structs.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

typedef struct { int x; char c; } T;

void echanger(void *a, void *b, size_t taille)
{
    (void)a;
    (void)b;
    (void)taille;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int x = 1, y = 2;
    echanger(&x, &y, sizeof x);
    CHECK(x == 2 && y == 1);

    T t1 = {1, 'a'};
    T t2 = {9, 'z'};
    echanger(&t1, &t2, sizeof t1);
    CHECK(t1.x == 9 && t1.c == 'z');
    CHECK(t2.x == 1 && t2.c == 'a');

    OK("échange générique");
    return 0;
}
