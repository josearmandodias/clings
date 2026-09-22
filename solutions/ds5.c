#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *creer(const int *valeurs, size_t n)
{
    Noeud *tete = NULL;
    for (size_t i = n; i > 0; i--) {
        Noeud *x = malloc(sizeof(*x));
        if (!x) return tete;
        x->valeur  = valeurs[i - 1];
        x->suivant = tete;
        tete = x;
    }
    return tete;
}

void liberer(Noeud *tete)
{
    while (tete) {
        Noeud *suivant = tete->suivant;
        free(tete);
        tete = suivant;
    }
}

Noeud *inverser(Noeud *tete)
{
    Noeud *prec = NULL;
    while (tete) {
        Noeud *suivant = tete->suivant;
        tete->suivant  = prec;
        prec           = tete;
        tete           = suivant;
    }
    return prec;
}

int main(void)
{
    const int vals[] = {1, 2, 3};

    CHECK(inverser(NULL) == NULL);   /* liste vide */

    Noeud *t = creer(vals, 3);
    t = inverser(t);
    CHECK(t && t->valeur == 3);
    CHECK(t->suivant && t->suivant->valeur == 2);
    CHECK(t->suivant->suivant && t->suivant->suivant->valeur == 1);
    CHECK(t->suivant->suivant->suivant == NULL);

    const int un[] = {7};
    Noeud *s = creer(un, 1);
    s = inverser(s);   /* un seul element : inchange */
    CHECK(s && s->valeur == 7 && s->suivant == NULL);

    liberer(t);
    liberer(s);
    CHECK_NO_LEAK();
    OK("inversion de liste");
    return 0;
}
