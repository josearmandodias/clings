#include <string.h>
#include "clings.h"

typedef struct { int x; char c; } T;

void echanger(void *a, void *b, size_t taille)
{
    unsigned char *pa = a;
    unsigned char *pb = b;
    for (size_t i = 0; i < taille; i++) {
        unsigned char tmp = pa[i];
        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

int main(void)
{
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
