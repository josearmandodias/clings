// Le "array decay" : dès qu'un tableau est passé à une fonction, il se
// dégrade en simple pointeur sur son premier élément. À l'intérieur,
// `sizeof(tab)` vaut la taille d'un pointeur (8 octets), plus celle du
// tableau. L'information de longueur est perdue.
//
// C'est pour ça que toute fonction C qui prend un tableau prend aussi sa
// longueur. Corrige `somme` et son appel.


// I AM NOT DONE

#include "clings.h"

int somme(const int *tab)
{
    int total = 0;
    size_t n = sizeof(tab) / sizeof(tab[0]);   /* faux : vaut 2 */
    for (size_t i = 0; i < n; i++) {
        total += tab[i];
    }
    return total;
}

int main(void)
{
    int valeurs[] = {1, 2, 3, 4, 5};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(sizeof(valeurs) / sizeof(valeurs[0]) == 5);   /* ici, ca marche */
    CHECK(somme(valeurs, 5) == 15);

    int un[] = {7};
    CHECK(somme(un, 1) == 7);          /* un seul element */
    CHECK(somme(un, 0) == 0);          /* rien a sommer */
    OK("un tableau se passe toujours avec sa longueur");
    return 0;
}
