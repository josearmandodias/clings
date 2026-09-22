// Comme pour inverser un tableau, on echange les extremites de la chaine
// jusqu'au milieu... a une difference pres : il faut d'abord connaitre sa
// longueur, et surtout ne pas ecraser le '\0'.
//
// `inverser` renverse `s` en place. Complete-la.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

void inverser(char *s)
{
    /* TODO */
    (void)s;
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

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(a, "cba") == 0);
    CHECK(strcmp(b, "") == 0);
    CHECK(strcmp(c, "ba") == 0);
    CHECK(strcmp(d, "kayak") == 0);
    OK("inverser une chaine");
    return 0;
}
