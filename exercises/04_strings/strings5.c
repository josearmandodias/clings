// `ma_strcmp` compare deux chaines caractere par caractere, en comparant les
// octets comme des `unsigned char` (c'est ce que garantit la norme).
//
// Des que deux caracteres different, leur difference donne le signe du
// resultat ; si l'une est un prefixe de l'autre, la plus courte est plus
// petite.
//
// Renvoie une valeur < 0, 0 ou > 0. Complete-la.


// I AM NOT DONE

#include "clings.h"

int ma_strcmp(const char *a, const char *b)
{
    /* TODO */
    (void)a;
    (void)b;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
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
