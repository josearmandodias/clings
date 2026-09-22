// Une struct qui possede une chaine doit allouer cette chaine a part : le
// pointeur `nom` ne suffit pas, il faut copier les octets.
//
// `personne_creer` alloue une Personne et une copie de `nom`.
// `personne_liberer` libere les deux, dans le bon ordre.
//
// `strlen(nom) + 1` : n'oublie pas l'octet terminateur '\0'.


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
    /* TODO */
    (void)nom;
    (void)age;
    return NULL;
}

void personne_liberer(Personne *p)
{
    /* TODO */
    (void)p;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    Personne *p = personne_creer("Ada", 36);
    CHECK(p != NULL);
    CHECK(strcmp(p->nom, "Ada") == 0);
    CHECK(p->age == 36);

    personne_liberer(p);
    CHECK_NO_LEAK();
    OK("struct proprietaire d'une chaine");
    return 0;
}
