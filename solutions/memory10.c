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
    Personne *c = malloc(sizeof(*c));
    if (c == NULL) {
        return NULL;
    }
    c->nom = malloc(strlen(p->nom) + 1);
    if (c->nom == NULL) {
        free(c);
        return NULL;
    }
    strcpy(c->nom, p->nom);
    c->age = p->age;
    return c;
}

int main(void)
{
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
