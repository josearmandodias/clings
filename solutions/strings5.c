#include "clings.h"

int ma_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b) {
        a++;
        b++;
    }
    return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

int main(void)
{
    CHECK(ma_strcmp("abc", "abc") == 0);
    CHECK(ma_strcmp("", "") == 0);

    CHECK(ma_strcmp("abc", "abd") < 0);
    CHECK(ma_strcmp("abd", "abc") > 0);

    CHECK(ma_strcmp("ab", "abc") < 0);   /* prefixe */
    CHECK(ma_strcmp("abc", "ab") > 0);

    CHECK(ma_strcmp("", "x") < 0);
    CHECK(ma_strcmp("x", "") > 0);
    OK("strcmp a la main");
    return 0;
}
