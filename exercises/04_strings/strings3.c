// Réimplémenter la libc est le meilleur exercice de pointeurs qui soit :
// tu ne peux plus te cacher derrière une abstraction.
//
// Écris `ma_strlen` et `ma_strcpy` sans utiliser <string.h>.
// ma_strcpy renvoie dst, comme la vraie.


// I AM NOT DONE

#include "clings.h"

size_t ma_strlen(const char *s)
{
    /* TODO */
    (void)s;
    return 0;
}

char *ma_strcpy(char *dst, const char *src)
{
    /* TODO */
    (void)src;
    return dst;
}

int main(void)
{
    char buf[32];

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(ma_strlen("") == 0);
    CHECK(ma_strlen("bonjour") == 7);

    CHECK(ma_strcpy(buf, "salut") == buf);
    CHECK(ma_strlen(buf) == 5);
    CHECK(buf[5] == '\0');

    ma_strcpy(buf, "");
    CHECK(buf[0] == '\0');

    char grand[32];
    CHECK(ma_strcpy(grand, "abcdefghijklmnopqrstuvwxyz01234") == grand);  /* 31 caracteres */
    CHECK(ma_strlen(grand) == 31);
    CHECK(grand[31] == '\0');       /* pile a la borne du tampon */
    OK("strlen et strcpy a la main");
    return 0;
}
