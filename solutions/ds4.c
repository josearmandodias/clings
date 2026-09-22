#define CLINGS_TRACK_ALLOC
#include "clings.h"

typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *ajouter_tete(Noeud *tete, int valeur)
{
    Noeud *n = malloc(sizeof(*n));
    if (!n) return tete;
    n->valeur  = valeur;
    n->suivant = tete;
    return n;
}

void liberer(Noeud *tete)
{
    while (tete) {
        Noeud *suivant = tete->suivant;
        free(tete);
        tete = suivant;
    }
}

Noeud *supprimer(Noeud *tete, int v)
{
    Noeud **lien = &tete;
    while (*lien && (*lien)->valeur != v)
        lien = &(*lien)->suivant;

    if (*lien) {
        Noeud *cible = *lien;
        *lien = cible->suivant;
        free(cible);
    }
    return tete;
}

int main(void)
{
    Noeud *t = NULL;
    for (int i = 5; i >= 1; i--) t = ajouter_tete(t, i);   /* 1,2,3,4,5 */

    t = supprimer(t, 3);   /* au milieu */
    const Noeud *c = t;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 4); c = c->suivant;
    CHECK(c && c->valeur == 5); c = c->suivant;
    CHECK(c == NULL);

    t = supprimer(t, 1);   /* en tete */
    CHECK(t && t->valeur == 2);

    t = supprimer(t, 5);   /* en queue */
    c = t;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 4); c = c->suivant;
    CHECK(c == NULL);

    t = supprimer(t, 9);   /* valeur absente : liste inchangee */
    CHECK(t && t->valeur == 2);
    CHECK(t->suivant && t->suivant->valeur == 4);
    CHECK(t->suivant->suivant == NULL);

    liberer(t);
    CHECK_NO_LEAK();
    OK("suppression dans une liste");
    return 0;
}
