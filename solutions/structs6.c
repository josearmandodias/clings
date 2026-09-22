#include "clings.h"

typedef struct {
    int  b;
    char a;
    char c;
} Melange;

int main(void)
{
    Melange m = {.a = 1, .b = 2, .c = 3};

    CHECK(sizeof(Melange) == 8);
    CHECK(m.a == 1);
    CHECK(m.b == 2);
    CHECK(m.c == 3);
    OK("ordre des champs et padding");
    return 0;
}
