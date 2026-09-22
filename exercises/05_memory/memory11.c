// Chaque `return` doit rendre ce que la fonction a emprunte. Ici `valider`
// alloue une copie de `s` mais ne la libere pas sur tous ses chemins : chaque
// appel qui sort sans free laisse fuir un bloc.
//
// `valider` renvoie 1 si `s` n'est pas vide et ne contient que des chiffres,
// 0 sinon. Corrige les sorties pour qu'aucun bloc ne fuie.


// I AM NOT DONE

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

    if (copie[0] == '\0') {
        return 0;                 /* TODO: sortie qui fuit */
    }
    for (size_t i = 0; copie[i] != '\0'; i++) {
        if (!isdigit((unsigned char)copie[i])) {
            free(copie);
            return 0;
        }
    }
    return 1;                     /* TODO: sortie qui fuit */
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    for (int i = 0; i < 3; i++) {
        CHECK(valider("123") == 1);
        CHECK(valider("") == 0);
        CHECK(valider("12a") == 0);
    }
    CHECK_NO_LEAK();
    OK("liberer sur tous les chemins");
    return 0;
}
