// Double free : libérer deux fois le même bloc corrompt l'allocateur.
// Le cas typique est celui d'ici : deux variables pointent sur le même bloc,
// et chacune croit en être propriétaire.
//
// `copie` ne fait qu'emprunter le pointeur — c'est un alias, pas un
// propriétaire. Décide qui possède quoi, et corrige.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

int main(void)
{
    char *original = malloc(8);
    CHECK(original != NULL);
    strcpy(original, "abc");

    char *copie = original;
    CHECK(strcmp(copie, "abc") == 0);

    free(copie);
    free(original);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    free(NULL);                 /* liberer NULL est inoffensif */
    CHECK_NO_LEAK();
    OK("un seul proprietaire, un seul free");
    return 0;
}
