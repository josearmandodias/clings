// Fusionner deux listes triees croissantes en une seule liste triee, en
// REUTILISANT les noeuds existants (aucune allocation). Renvoie la tete.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `fusionner`.


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

Noeud *fusionner(Noeud *a, Noeud *b)
{
    /* TODO */
    (void)a;
    (void)b;
    return NULL;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int ta[] = {1, 3, 5};
    int tb[] = {2, 4, 6};
    Noeud *a = depuis_tableau(ta, 3);
    Noeud *b = depuis_tableau(tb, 3);
    Noeud *f = fusionner(a, b);
    const Noeud *c = f;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c && c->valeur == 4); c = c->suivant;
    CHECK(c && c->valeur == 5); c = c->suivant;
    CHECK(c && c->valeur == 6); c = c->suivant;
    CHECK(c == NULL);
    liberer(f);

    int ea[] = {1, 2, 2};
    int eb[] = {2, 3};
    a = depuis_tableau(ea, 3);
    b = depuis_tableau(eb, 2);
    f = fusionner(a, b);
    c = f;
    CHECK(c && c->valeur == 1); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 2); c = c->suivant;
    CHECK(c && c->valeur == 3); c = c->suivant;
    CHECK(c == NULL);
    liberer(f);

    int x[] = {7, 8};
    a = depuis_tableau(x, 2);
    f = fusionner(a, NULL);          /* b vide : renvoie a */
    CHECK(f && f->valeur == 7 && f->suivant->valeur == 8);
    liberer(f);

    b = depuis_tableau(x, 2);
    f = fusionner(NULL, b);          /* a vide : renvoie b */
    CHECK(f && f->valeur == 7 && f->suivant->valeur == 8);
    liberer(f);

    CHECK(fusionner(NULL, NULL) == NULL);

    CHECK_NO_LEAK();
    OK("fusionner deux listes triees");
    return 0;
}
