// `realloc` peut deplacer le bloc : la bonne adresse est celle qu'il renvoie,
// pas forcement celle qu'on lui a donnee. Ecrire `tab = realloc(tab, ...)`
// perd le bloc d'origine si realloc echoue : il faut passer par un temporaire.
//
// `agrandir` renvoie un tableau de `nouveau` int gardant les `ancien`
// premieres valeurs, ou NULL (sans liberer `tab`) si l'allocation echoue.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

int *agrandir(int *tab, size_t ancien, size_t nouveau)
{
    /* TODO: agrandir reellement le bloc, sans le perdre en cas d'echec. */
    (void)tab;
    (void)ancien;
    (void)nouveau;
    return NULL;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int *tab = malloc(3 * sizeof(*tab));
    CHECK(tab != NULL);
    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;

    int *plus = agrandir(tab, 3, 6);
    CHECK(plus != NULL);
    CHECK(plus[0] == 1);
    CHECK(plus[1] == 2);
    CHECK(plus[2] == 3);

    plus[3] = 10;
    plus[4] = 20;
    plus[5] = 30;
    CHECK(plus[5] == 30);

    free(plus);
    CHECK_NO_LEAK();
    OK("realloc sans perdre le bloc");
    return 0;
}
