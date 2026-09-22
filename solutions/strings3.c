#include "clings.h"

size_t ma_strlen(const char *s)
{
    const char *d = s;
    while (*d) d++;
    return (size_t)(d - s);
}

char *ma_strcpy(char *dst, const char *src)
{
    char *debut = dst;
    while ((*dst++ = *src++) != '\0')
        ;
    return debut;
}

int main(void)
{
    char buf[32];

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
