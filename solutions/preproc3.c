#include "clings.h"

#define CONCAT(a, b) a##b

static int mon_petit_test(void)
{
    return 42;
}

int main(void)
{
    CHECK(CONCAT(2, 3) == 23);
    CHECK(CONCAT(mon_petit_, test)() == 42);
    OK("collage de jetons");
    return 0;
}
