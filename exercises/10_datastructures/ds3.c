// Une liste chainee triee garde ses elements ordonnes des l'insertion. On
// avance jusqu'au premier noeud plus grand (ou egal), puis on enchaine le
// nouveau noeud juste avant lui ; s'il n'y en a pas, on ajoute en queue.
//
// `liberer` est fournie comme utilitaire. Complete `inserer` : renvoie la
// (nouvelle) tete de la liste triee par ordre croissant.


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

Noeud *inserer(Noeud *tete, int v)
{
    /* TODO */
    (void)v;
    return tete;
}

int main(void)
{
    Noeud *t = NULL;

    // ---------------------------- NE TOUCHE PAS -----------------------------
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
