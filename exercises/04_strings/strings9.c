// Un palindrome se lit pareil dans les deux sens. Ici on ignore la casse
// (mais pas les espaces) : deux caracteres sont egaux si
// tolower((unsigned char)c) est identique.
//
// Attention : `tolower` attend un `unsigned char` converti en `int`, sinon le
// comportement est indefini pour les octets accentues.
//
// `est_palindrome` renvoie 1 ou 0. Complete-la.


// I AM NOT DONE

#include <ctype.h>
#include <string.h>
#include "clings.h"

int est_palindrome(const char *s)
{
    /* TODO */
    (void)s;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(est_palindrome("Kayak") == 1);
    CHECK(est_palindrome("Level") == 1);
    CHECK(est_palindrome("Hello") == 0);
    CHECK(est_palindrome("") == 1);
    CHECK(est_palindrome("A") == 1);
    CHECK(est_palindrome("abba") == 1);
    OK("palindrome insensible a la casse");
    return 0;
}
