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

int main(void)
{
    Personne *p = personne_creer("Ada", 36);
    CHECK(p != NULL);
    CHECK(strcmp(p->nom, "Ada") == 0);
    CHECK(p->age == 36);

    personne_liberer(p);
    CHECK_NO_LEAK();
    OK("struct proprietaire d'une chaine");
    return 0;
}
