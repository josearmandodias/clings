#include <string.h>
#include "clings.h"

int est_palindrome_rec(const char *s, int debut, int fin)
{
    if (fin - debut <= 1) {
        return 1;
    }
    if (s[debut] != s[fin - 1]) {
        return 0;
    }
    return est_palindrome_rec(s, debut + 1, fin - 1);
}

int main(void)
{
    const char *kayak = "kayak";
    const char *ab    = "ab";
    const char *vide  = "";
    const char *a     = "a";
    const char *abba  = "abba";

    CHECK(est_palindrome_rec(kayak, 0, (int)strlen(kayak)) == 1);
    CHECK(est_palindrome_rec(ab, 0, (int)strlen(ab)) == 0);
    CHECK(est_palindrome_rec(vide, 0, 0) == 1);
    CHECK(est_palindrome_rec(a, 0, 1) == 1);
    CHECK(est_palindrome_rec(abba, 0, 4) == 1);
    OK("palindrome recursif");
    return 0;
}
