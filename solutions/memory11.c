#define CLINGS_TRACK_ALLOC
#include <ctype.h>
#include <string.h>
#include "clings.h"

int valider(const char *s)
{
    char *copie = malloc(strlen(s) + 1);
    if (copie == NULL) {
        return 0;
    }
    strcpy(copie, s);

    int ok = copie[0] != '\0';
    for (size_t i = 0; ok && copie[i] != '\0'; i++) {
        if (!isdigit((unsigned char)copie[i])) {
            ok = 0;
        }
    }

    free(copie);
    return ok;
}

int main(void)
{
    for (int i = 0; i < 3; i++) {
        CHECK(valider("123") == 1);
        CHECK(valider("") == 0);
        CHECK(valider("12a") == 0);
    }
    CHECK_NO_LEAK();
    OK("liberer sur tous les chemins");
    return 0;
}
