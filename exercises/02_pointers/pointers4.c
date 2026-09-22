// `const char *s` : le contenu pointé est en lecture seule.
// `char * const s` : c'est le pointeur qui ne peut pas bouger.
// La première forme est celle qui compte : elle documente qu'une fonction
// ne modifiera pas ce que tu lui prêtes, et le compilateur le vérifie.
//
// `compte_a` ne doit pas modifier la chaîne. Corrige sa signature et son
// implémentation pour que tout compile.


// I AM NOT DONE

#include "clings.h"

int compte_a(char *s)
{
    int n = 0;
    while (*s) {
        if (*s == 'a') {
            *s = 'A';          /* effet de bord non voulu */
            n++;
        }
        s++;
    }
    return n;
}

int main(void)
{
    const char *texte = "banana";

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(compte_a(texte) == 3);
    CHECK(texte[1] == 'a');            /* la chaine est intacte */
    CHECK(compte_a("") == 0);          /* chaine vide */
    CHECK(compte_a("xyz") == 0);       /* aucun 'a' */
    CHECK(compte_a("aaa") == 3);
    CHECK(compte_a("Aaa") == 2);       /* la casse compte */
    OK("const correctness");
    return 0;
}
