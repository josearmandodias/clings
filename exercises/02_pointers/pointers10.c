// Une fonction peut renvoyer un pointeur vers un élément d'un tableau qu'on
// lui a prêté : l'adresse reste valide tant que le tableau vit. C'est le
// « pointeur emprunté » (borrowed) de Rust.
//
// `chercher` renvoie l'adresse de la PREMIÈRE occurrence de `valeur`, ou
// `NULL` si elle est absente (y compris quand `n == 0`).
// Compare donc des adresses : `== &tab[i]`, pas seulement la valeur.


// I AM NOT DONE

#include "clings.h"

const int *chercher(const int *tab, size_t n, int valeur)
{
    (void)n;
    (void)valeur;
    return &tab[0];
}

int main(void)
{
    const int tab[] = {4, 8, 15, 16, 23, 42};

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(chercher(tab, 6, 15) == &tab[2]);
    CHECK(chercher(tab, 6, 100) == NULL);
    CHECK(chercher(tab, 0, 4) == NULL);
    OK("retour de pointeur");
    return 0;
}
