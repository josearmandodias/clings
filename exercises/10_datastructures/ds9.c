// Une table de hachage associe une cle a une valeur. Le hachage donne un
// indice de seau ; plusieurs cles peuvent tomber dans le meme seau : on les
// chaine dans une liste. Chaque entree possede donc sa propre copie de la cle.
//
// `hash` est fourni. Complete `table_put` (ecrase si la cle existe), `table_get`
// (1 si trouve) et `table_free` (libere toutes les entrees et leurs cles).


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

#define NB_BUCKETS 8

typedef struct Entree {
    char          *cle;
    int            valeur;
    struct Entree *suivant;
} Entree;

typedef struct {
    Entree *buckets[NB_BUCKETS];
} Table;

unsigned hash(const char *cle)
{
    unsigned h = 0;
    for (const unsigned char *p = (const unsigned char *)cle; *p; p++)
        h = h * 31u + *p;
    return h;
}

int table_put(Table *t, const char *cle, int valeur)
{
    /* TODO */
    (void)t;
    (void)cle;
    (void)valeur;
    return 0;
}

int table_get(const Table *t, const char *cle, int *valeur)
{
    /* TODO */
    (void)t;
    (void)cle;
    (void)valeur;
    return 0;
}

void table_free(Table *t)
{
    /* TODO */
    (void)t;
}

int main(void)
{
    Table t = {{0}};
    int   v = 0;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(table_get(&t, "absent", &v) == 0);

    CHECK(table_put(&t, "ada", 36) == 1);
    CHECK(table_put(&t, "bob", 7) == 1);
    CHECK(table_put(&t, "carla", 21) == 1);
    CHECK(table_put(&t, "ada", 37) == 1);   /* ecrasement */

    CHECK(table_get(&t, "ada", &v) == 1 && v == 37);
    CHECK(table_get(&t, "bob", &v) == 1 && v == 7);
    CHECK(table_get(&t, "carla", &v) == 1 && v == 21);
    CHECK(table_get(&t, "dora", &v) == 0);

    table_free(&t);
    CHECK_NO_LEAK();
    OK("table de hachage");
    return 0;
}
