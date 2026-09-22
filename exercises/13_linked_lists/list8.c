// Detecter la presence d'un cycle avec l'algorithme du lievre et de la tortue.
//
// `depuis_tableau` et `liberer` sont fournies. Complete `a_un_cycle` (renvoie
// 1 si la liste boucle, 0 sinon).


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

int a_un_cycle(const Noeud *tete)
{
    /* TODO */
    (void)tete;
    return 0;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int t[] = {1, 2, 3, 4, 5};
    Noeud *l = depuis_tableau(t, 5);
    CHECK(a_un_cycle(l) == 0);           /* pas de cycle */

    /* on cree un cycle : le dernier noeud pointe vers le 2e */
    Noeud *dernier = l;
    while (dernier->suivant) dernier = dernier->suivant;
    dernier->suivant = l->suivant;
    CHECK(a_un_cycle(l) == 1);
    dernier->suivant = NULL;             /* CASSER le cycle avant de liberer */
    liberer(l);

    Noeud *seul = depuis_tableau(t, 1);
    seul->suivant = seul;                /* noeud qui pointe sur lui-meme */
    CHECK(a_un_cycle(seul) == 1);
    seul->suivant = NULL;                /* casser avant de liberer */
    liberer(seul);

    CHECK(a_un_cycle(NULL) == 0);

    CHECK_NO_LEAK();
    OK("detecter un cycle");
    return 0;
}
