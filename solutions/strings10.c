#include "clings.h"

const char *ma_strchr(const char *s, int c)
{
    char cible = (char)c;

    for (;; s++) {
        if (*s == cible) {
            return s;
        }
        if (*s == '\0') {
            return NULL;
        }
    }
}

int main(void)
{
    const char *ch = "bonjour";
    const char *vide = "";

    CHECK(ma_strchr(ch, 'n') == &ch[2]);
    CHECK(ma_strchr(ch, 'z') == NULL);
    CHECK(ma_strchr(ch, '\0') == &ch[7]);   /* le terminateur */
    CHECK(ma_strchr(vide, 'a') == NULL);
    CHECK(ma_strchr(vide, '\0') == vide);
    OK("strchr a la main");
    return 0;
}
