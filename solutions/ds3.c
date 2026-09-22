#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

void liberer(Noeud *tete)
{
    while (tete) {
        Noeud *suivant = tete->suivant;
        free(tete);
        tete = suivant;
    }
}

Noeud *inserer(Noeud *tete, int v)
{
    Noeud *n = malloc(sizeof(*n));
    if (!n) return tete;
    n->valeur  = v;
    n->suivant = NULL;

    if (!tete || v < tete->valeur) {
        n->suivant = tete;
        return n;
    }

    Noeud *c = tete;
    while (c->suivant && c->suivant->valeur < v)
        c = c->suivant;

    n->suivant  = c->suivant;
    c->suivant  = n;
    return tete;
}

int main(void)
{
    Noeud *t = NULL;

    t = inserer(t, 3);
    t = inserer(t, 1);   /* en tete */
    t = inserer(t, 5);   /* en queue */
    t = inserer(t, 2);   /* au milieu */
    t = inserer(t, 1);   /* doublon */

    const Noeud *c = t;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 5); c = c->suivant;
    CHECK(c == NULL);

    liberer(t);
    CHECK_NO_LEAK();
    OK("insertion triee");
    return 0;
}
