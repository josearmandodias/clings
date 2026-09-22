// Copier une liste : une liste INDEPENDANTE avec de nouveaux noeuds, les memes
// valeurs dans le meme ordre.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `copier`.

#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

void liberer(Noeud *tete)
{
    while (tete) { Noeud *s = tete->suivant; free(tete); tete = s; }
}

/* construit une liste dans l'ordre du tableau */
Noeud *depuis_tableau(const int *tab, size_t n)
{
    Noeud *tete = NULL, *queue = NULL;
    for (size_t i = 0; i < n; i++) {
        Noeud *x = malloc(sizeof *x);
        if (!x) { liberer(tete); return NULL; }
        x->valeur = tab[i]; x->suivant = NULL;
        if (queue) queue->suivant = x; else tete = x;
        queue = x;
    }
    return tete;
}

Noeud *copier(const Noeud *tete)
{
    Noeud *tete_copie = NULL, *queue = NULL;
    for (const Noeud *c = tete; c; c = c->suivant) {
        Noeud *n = malloc(sizeof *n);
        if (!n) { liberer(tete_copie); return NULL; }
        n->valeur = c->valeur;
        n->suivant = NULL;
        if (queue) queue->suivant = n; else tete_copie = n;
        queue = n;
    }
    return tete_copie;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int t[] = {1, 2, 3};
    Noeud *orig = depuis_tableau(t, 3);
    Noeud *cop  = copier(orig);

    CHECK(cop && cop->valeur == 1);
    CHECK(cop->suivant && cop->suivant->valeur == 2);
    CHECK(cop->suivant->suivant && cop->suivant->suivant->valeur == 3);
    CHECK(cop->suivant->suivant->suivant == NULL);

    /* chaque noeud de la copie est une adresse differente */
    CHECK(cop != orig);
    CHECK(cop->suivant != orig->suivant);
    CHECK(cop->suivant->suivant != orig->suivant->suivant);

    /* modifier la copie ne change pas l'original */
    cop->valeur = 99;
    cop->suivant->suivant->valeur = 77;
    CHECK(orig->valeur == 1);
    CHECK(orig->suivant->suivant->valeur == 3);

    liberer(orig);
    liberer(cop);

    CHECK(copier(NULL) == NULL);

    CHECK_NO_LEAK();
    OK("copier une liste");
    return 0;
}
