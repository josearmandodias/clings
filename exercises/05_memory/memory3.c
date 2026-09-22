// Use-after-free : après free(p), p contient toujours une adresse, mais elle
// ne t'appartient plus. La lire ou l'écrire est un comportement indéfini —
// souvent silencieux, parfois exploitable.
//
// Deux réflexes à prendre :
//   - libérer le plus tard possible, à un seul endroit ;
//   - mettre le pointeur à NULL juste après le free.
//
// Réordonne main pour que le programme soit correct. ASan te dira si tu
// te trompes.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

int main(void)
{
    char *buf = malloc(16);
    CHECK(buf != NULL);
    strcpy(buf, "salut");

    free(buf);

    size_t n = strlen(buf);
    char premier = buf[0];

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(n == 5);
    CHECK(premier == 's');
    CHECK(buf == NULL);
    free(buf);                  /* buf vaut NULL : inoffensif */
    CHECK_NO_LEAK();
    OK("aucun acces apres liberation");
    return 0;
}
