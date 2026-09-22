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

Noeud *ajouter_queue(Noeud *tete, int v)
{
    Noeud *n = malloc(sizeof(*n));
    if (!n) return tete;
    n->valeur  = v;
    n->suivant = NULL;

    if (!tete) return n;

    Noeud *c = tete;
    while (c->suivant) c = c->suivant;
    c->suivant = n;
    return tete;
}

int main(void)
{
    Noeud *t = NULL;

    t = ajouter_queue(t, 1);   /* liste vide -> un element */
    CHECK(t && t->valeur == 1 && t->suivant == NULL);

    t = ajouter_queue(t, 2);
    t = ajouter_queue(t, 3);
    t = ajouter_queue(t, 4);

    const Noeud *c = t;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 4); c = c->suivant;
    CHECK(c == NULL);

    liberer(t);
    CHECK_NO_LEAK();
    OK("ajout en queue");
    return 0;
}
