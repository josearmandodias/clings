#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

char *duplique(const char *s)
{
    size_t n = strlen(s);
    char  *copie = malloc(n + 1);
    if (!copie) return NULL;
    memcpy(copie, s, n + 1);
    return copie;
}

int main(void)
{
    char *a = duplique("bonjour");
    char *b = duplique("monde");

    CHECK(a && b);
    CHECK(strcmp(a, "bonjour") == 0);
    CHECK(strcmp(b, "monde") == 0);
    free(a);
    free(b);

    for (int i = 0; i < 3; i++) {
        char *tmp = duplique("boucle");
        CHECK(tmp != NULL);
        free(tmp);
    }

    char *vide = duplique("");
    CHECK(vide != NULL && vide[0] == '\0');
    free(vide);

    free(NULL);                 /* liberer NULL est inoffensif */
    CHECK_NO_LEAK();
    OK("chaque malloc a son free");
    return 0;
}
