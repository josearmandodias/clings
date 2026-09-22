// Le C n'a pas d'exceptions. La convention est : valeur de retour = statut,
// et en cas d'échec système, la variable globale `errno` dit pourquoi.
//
// Règles pratiques :
//   - on ne teste errno que si l'appel a signalé une erreur ;
//   - on remet errno à 0 avant l'appel quand la fonction peut renvoyer une
//     valeur légitime indistinguable d'une erreur (c'est le cas de strtol) ;
//   - strerror(errno) donne le message lisible.
//
// Complète `lire_entier` : conversion stricte d'une chaîne en long.
// Renvoie 0 en cas de succès, -1 sinon (chaîne vide, caractères parasites,
// ou dépassement). En cas de succès seulement, écrit le résultat dans *out.


// I AM NOT DONE

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "clings.h"

int lire_entier(const char *s, long *out)
{
    /* TODO: utilise strtol(s, &fin, 10) */
    (void)s;
    (void)out;
    return -1;
}

int main(void)
{
    long v = 0;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(lire_entier("123", &v) == 0 && v == 123);
    CHECK(lire_entier("-7", &v) == 0 && v == -7);

    CHECK(lire_entier("", &v) == -1);
    CHECK(lire_entier("12abc", &v) == -1);
    CHECK(lire_entier("99999999999999999999999999", &v) == -1);

    /* errno n'est pas remis a zero tout seul : ce cas verifie qu'on l'a fait. */
    CHECK(lire_entier("0", &v) == 0 && v == 0);

    CHECK(lire_entier("   42", &v) == 0 && v == 42);   /* strtol saute les blancs */
    CHECK(lire_entier("+5", &v) == 0 && v == 5);

    v = 777;
    CHECK(lire_entier("abc", &v) == -1);
    CHECK(v == 777);                                    /* *out intact en cas d'echec */
    OK("gestion d'erreur a la C");
    return 0;
}
