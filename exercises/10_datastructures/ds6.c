// Ajouter en queue oblige a parcourir la liste jusqu'au dernier noeud, car on
// ne dispose que de la tete. Si la liste est vide, le nouveau noeud devient la
// tete : c'est la seule fois ou la tete change.
//
// `liberer` est fournie. Complete `ajouter_queue` : renvoie la tete de la
// liste (inchangee sauf si elle etait vide).


// I AM NOT DONE

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
    /* TODO */
    (void)v;
    return tete;
}

int main(void)
{
    Noeud *t = NULL;

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
