// Palindrome récursif : une chaîne est un palindrome si ses deux extrémités
// sont égales et que l'intérieur l'est aussi.
//
// `s[debut..fin[` : `fin` est exclu. Un intervalle de longueur 0 ou 1 est
// toujours un palindrome. Écris `est_palindrome_rec` récursivement.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

int est_palindrome_rec(const char *s, int debut, int fin)
{
    /* TODO */
    (void)s;
    (void)debut;
    (void)fin;
    return 0;
}

int main(void)
{
    const char *kayak = "kayak";
    const char *ab    = "ab";
    const char *vide  = "";
    const char *a     = "a";
    const char *abba  = "abba";

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(est_palindrome_rec(kayak, 0, (int)strlen(kayak)) == 1);
    CHECK(est_palindrome_rec(ab, 0, (int)strlen(ab)) == 0);
    CHECK(est_palindrome_rec(vide, 0, 0) == 1);
    CHECK(est_palindrome_rec(a, 0, 1) == 1);
    CHECK(est_palindrome_rec(abba, 0, 4) == 1);
    OK("palindrome recursif");
    return 0;
}
