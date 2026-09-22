// Chaque malloc a un propriétaire : quelqu'un doit décider quand libérer.
// C'est la question centrale du C, et c'est précisément celle que Rust
// répond à ta place avec l'ownership.
//
// Ici il y a une fuite. `duplique` alloue, mais personne ne libère.
// Ajoute les free() qui manquent, au bon endroit.
//
// (clings compte les allocations : CHECK_NO_LEAK échoue s'il en reste.)


// I AM NOT DONE

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

    for (int i = 0; i < 3; i++) {
        char *tmp = duplique("boucle");
        CHECK(tmp != NULL);
    }

    // ---------------------------- NE TOUCHE PAS -----------------------------
    char *vide = duplique("");
    CHECK(vide != NULL && vide[0] == '\0');
    free(vide);

    free(NULL);                 /* liberer NULL est inoffensif */
    CHECK_NO_LEAK();
    OK("chaque malloc a son free");
    return 0;
}
