#include "clings.h"

int compte_a(const char *s)
{
    int n = 0;
    while (*s) {
        if (*s == 'a') n++;
        s++;
    }
    return n;
}

int main(void)
{
    const char *texte = "banana";

    CHECK(compte_a(texte) == 3);
    CHECK(texte[1] == 'a');            /* la chaine est intacte */
    CHECK(compte_a("") == 0);          /* chaine vide */
    CHECK(compte_a("xyz") == 0);       /* aucun 'a' */
    CHECK(compte_a("aaa") == 3);
    CHECK(compte_a("Aaa") == 2);       /* la casse compte */
    OK("const correctness");
    return 0;
}
