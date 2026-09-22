#include <math.h>
#include "clings.h"

int presque_egaux(double a, double b)
{
    return fabs(a - b) < 1e-9;
}

int main(void)
{
    CHECK(presque_egaux(0.1 + 0.2, 0.3) == 1);
    CHECK(presque_egaux(1.0, 1.0) == 1);
    CHECK(presque_egaux(1.0, 1.1) == 0);
    OK("comparaison flottante");
    return 0;
}
