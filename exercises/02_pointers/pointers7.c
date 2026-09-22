// `const` se lit de droite à gauche dans un type. `const char *const *mots`
// est un pointeur modifiable vers des pointeurs CONSTANTS vers des caractères
// constants : on peut lire les chaînes, mais pas déplacer les éléments du
// tableau.
//
// La signature de `longueur_totale` a perdu le `const` du milieu, et le
// compilateur refuse alors le tableau de test. Rétablis-la, puis renvoie la
// somme des `strlen` des `n` mots.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

size_t longueur_totale(const char **mots, size_t n)
{
    (void)mots;
    (void)n;
    return 0;
}

int main(void)
{
    static const char *const mots[] = {"un", "deux", "trois"};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(longueur_totale(mots, 3) == 11);
    CHECK(longueur_totale(mots, 0) == 0);
    OK("const à plusieurs niveaux");
    return 0;
}
