// Un programme C peut être découpé en plusieurs fichiers .c, compilés
// séparément puis liés. Pour appeler une fonction définie ailleurs, le
// compilateur doit connaître sa DÉCLARATION : c'est le rôle du header.
//
// Ici, `modules2_table.c` (fourni, ne pas modifier) définit les fonctions, et
// `modules2_table.h` doit les déclarer. Ce header est incomplet : il manque
// les gardes d'inclusion et le prototype de `somme_tableau`.
// Corrige le header, pas les autres fichiers.
//
// (clings compile automatiquement tous les `modules2_*.c` du dossier.)



#include <stddef.h>
#include "modules2_table.h"
#include "clings.h"

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    const int tab[] = {4, 9, 2};

    CHECK(max_tableau(tab, 3) == 9);
    CHECK(somme_tableau(tab, 3) == 15);
    OK("plusieurs fichiers");
    return 0;
}
