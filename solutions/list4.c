// Retirer TOUTES les occurrences d'une valeur et liberer les noeuds retires.
// La fonction renvoie la tete resultante (elle peut changer).
//
// `depuis_tableau` et `liberer` sont fournies. Complete `supprimer_tout`.

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

Noeud *supprimer_tout(Noeud *tete, int v)
{
    Noeud **lien = &tete;
    while (*lien) {
        if ((*lien)->valeur == v) {
            Noeud *cible = *lien;
            *lien = cible->suivant;
            free(cible);
        } else {
            lien = &(*lien)->suivant;
        }
    }
    return tete;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int a[] = {1, 1, 2, 1};
    Noeud *l = depuis_tableau(a, 4);
    l = supprimer_tout(l, 1);        /* doublons en tete : {2} */
    CHECK(l && l->valeur == 2 && l->suivant == NULL);
    liberer(l);

    int b[] = {1, 2, 2, 3};
    l = depuis_tableau(b, 4);
    l = supprimer_tout(l, 2);        /* au milieu : {1,3} */
    CHECK(l && l->valeur == 1);
    CHECK(l->suivant && l->suivant->valeur == 3 && l->suivant->suivant == NULL);
    liberer(l);

    int c[] = {1, 2, 3};
    l = depuis_tableau(c, 3);
    l = supprimer_tout(l, 9);        /* valeur absente : inchangee */
    CHECK(l && l->valeur == 1 && l->suivant->valeur == 2);
    liberer(l);

    int d[] = {4, 4, 4};
    l = depuis_tableau(d, 3);
    l = supprimer_tout(l, 4);        /* tous les elements */
    CHECK(l == NULL);
    liberer(l);

    CHECK_NO_LEAK();
    OK("supprimer toutes les occurrences");
    return 0;
}
