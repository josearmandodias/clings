// Le C ne vérifie aucune borne. Écrire dans tab[10] d'un tableau de 10
// éléments ne provoque pas d'erreur : ça écrase la mémoire voisine, et le
// bug se manifeste ailleurs, plus tard, sans rapport apparent.
//
// AddressSanitizer, lui, l'attrape immédiatement. Lance l'exercice, lis le
// rapport ASan (c'est le but de l'exercice : apprendre à le lire), puis
// corrige la boucle.


// I AM NOT DONE

#include "clings.h"

#define N 10

int main(void)
{
    int tab[N];

    for (int i = 0; i <= N; i++) {
        tab[i] = i * i;
    }

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(tab[0] == 0);
    CHECK(tab[1] == 1);
    CHECK(tab[5] == 25);
    CHECK(tab[N - 1] == 81);           /* dernier indice valide : N - 1 */
    OK("pas de depassement de tableau");
    return 0;
}
