// Sur une liste TRIEE, garder une seule occurrence de chaque valeur et liberer
// les doublons. Renvoie la tete (qui ne change pas ici).
//
// `depuis_tableau` et `liberer` sont fournies. Complete `sans_doublons`.


// I AM NOT DONE

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

Noeud *sans_doublons(Noeud *tete)
{
    /* TODO */
    return tete;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int t[] = {1, 1, 2, 3, 3, 3, 4};
    Noeud *l = depuis_tableau(t, 7);
    l = sans_doublons(l);
    const Noeud *c = l;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 4); c = c->suivant;
    CHECK(c == NULL);
    liberer(l);

    int p[] = {1, 2, 3};
    l = depuis_tableau(p, 3);
    l = sans_doublons(l);            /* sans doublons : inchangee */
    CHECK(l && l->valeur == 1);
    CHECK(l->suivant && l->suivant->valeur == 2);
    CHECK(l->suivant->suivant && l->suivant->suivant->valeur == 3);
    CHECK(l->suivant->suivant->suivant == NULL);
    liberer(l);

    int q[] = {5, 5, 5};
    l = depuis_tableau(q, 3);
    l = sans_doublons(l);            /* toutes egales : {5} */
    CHECK(l && l->valeur == 5 && l->suivant == NULL);
    liberer(l);

    CHECK(sans_doublons(NULL) == NULL);   /* vide */

    CHECK_NO_LEAK();
    OK("supprimer les doublons");
    return 0;
}
