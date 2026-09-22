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
    unsigned b = hash(cle) % NB_BUCKETS;

    for (Entree *e = t->buckets[b]; e; e = e->suivant) {
        if (strcmp(e->cle, cle) == 0) {
            e->valeur = valeur;   /* cle deja presente : on ecrase */
            return 1;
        }
    }

    Entree *e = malloc(sizeof(*e));
    if (!e) return 0;

    size_t n = strlen(cle);
    e->cle = malloc(n + 1);
    if (!e->cle) {
        free(e);
        return 0;
    }
    memcpy(e->cle, cle, n + 1);
    e->valeur   = valeur;
    e->suivant  = t->buckets[b];
    t->buckets[b] = e;
    return 1;
}

int table_get(const Table *t, const char *cle, int *valeur)
{
    unsigned b = hash(cle) % NB_BUCKETS;

    for (const Entree *e = t->buckets[b]; e; e = e->suivant) {
        if (strcmp(e->cle, cle) == 0) {
            if (valeur) *valeur = e->valeur;
            return 1;
        }
    }
    return 0;
}

void table_free(Table *t)
{
    for (size_t i = 0; i < NB_BUCKETS; i++) {
        Entree *e = t->buckets[i];
        while (e) {
            Entree *suivant = e->suivant;
            free(e->cle);
            free(e);
            e = suivant;
        }
        t->buckets[i] = NULL;
    }
}

int main(void)
{
    Table t = {{0}};
    int   v = 0;

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
