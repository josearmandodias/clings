// Copier une struct avec `*c = *p` recopie les pointeurs, pas ce qu'ils
// designent. Les deux Personne pointent alors vers le meme `nom` : modifier
// l'une modifie l'autre, et liberer les deux provoque un double free.
//
// `personne_creer` et `personne_liberer` sont fournis. Complete
// `personne_clone` pour realiser un vrai clonage profond : la copie doit
// posseder sa propre chaine.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

typedef struct {
    char *nom;
    int   age;
} Personne;

Personne *personne_creer(const char *nom, int age)
{
    Personne *p = malloc(sizeof(*p));
    if (p == NULL) {
        return NULL;
    }
    p->nom = malloc(strlen(nom) + 1);
    if (p->nom == NULL) {
        free(p);
        return NULL;
    }
    strcpy(p->nom, nom);
    p->age = age;
    return p;
}

void personne_liberer(Personne *p)
{
    if (p == NULL) {
        return;
    }
    free(p->nom);
    free(p);
}

Personne *personne_clone(const Personne *p)
{
    /* TODO: copie profonde, la chaine doit etre dupliquee. */
    Personne *c = malloc(sizeof(*c));
    if (c == NULL) {
        return NULL;
    }
    *c = *p;
    return c;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    Personne *p = personne_creer("Ada", 36);
    CHECK(p != NULL);

    Personne *c = personne_clone(p);
    CHECK(c != NULL);
    CHECK(c != p);
    CHECK(c->nom != p->nom);
    CHECK(strcmp(c->nom, p->nom) == 0);
    CHECK(c->age == p->age);

    c->nom[0] = 'B';
    CHECK(strcmp(p->nom, "Ada") == 0);

    personne_liberer(c);
    personne_liberer(p);
    CHECK_NO_LEAK();
    OK("clonage profond");
    return 0;
}
