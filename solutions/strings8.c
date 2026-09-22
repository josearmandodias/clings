#include <string.h>
#include "clings.h"

void inverser(char *s)
{
    size_t n = strlen(s);

    for (size_t i = 0; i < n / 2; i++) {
        char tmp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = tmp;
    }
}

int main(void)
{
    char a[] = "abc";
    char b[] = "";
    char c[] = "ab";
    char d[] = "kayak";

    inverser(a);
    inverser(b);
    inverser(c);
    inverser(d);

    CHECK(strcmp(a, "cba") == 0);
    CHECK(strcmp(b, "") == 0);
    CHECK(strcmp(c, "ba") == 0);
    CHECK(strcmp(d, "kayak") == 0);
    OK("inverser une chaine");
    return 0;
}
