#include <ctype.h>
#include <string.h>
#include "clings.h"

int est_palindrome(const char *s)
{
    size_t n = strlen(s);

    for (size_t i = 0; i < n / 2; i++) {
        if (tolower((unsigned char)s[i]) !=
            tolower((unsigned char)s[n - 1 - i])) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    CHECK(est_palindrome("Kayak") == 1);
    CHECK(est_palindrome("Level") == 1);
    CHECK(est_palindrome("Hello") == 0);
    CHECK(est_palindrome("") == 1);
    CHECK(est_palindrome("A") == 1);
    CHECK(est_palindrome("abba") == 1);
    OK("palindrome insensible a la casse");
    return 0;
}
