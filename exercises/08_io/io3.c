// Un fichier binaire contient les octets de la mémoire, sans conversion en
// texte. fwrite copie un bloc depuis la mémoire vers le fichier, fread fait
// l'inverse. On ouvre ces fichiers en mode binaire : "wb" et "rb".
//
// `sauver_point` écrit le contenu de `*p` dans le fichier ; `charger_point`
// le relit dans `*p`. Toutes deux renvoient 0 en cas de succès, -1 sinon.


// I AM NOT DONE

#include <stdio.h>
#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

int sauver_point(const char *chemin, const Point *p)
{
    /* TODO : fwrite(p, sizeof *p, 1, f) */
    (void)chemin;
    (void)p;
    return -1;
}

int charger_point(const char *chemin, Point *p)
{
    /* TODO : fread(p, sizeof *p, 1, f) */
    (void)chemin;
    (void)p;
    return -1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    const char *tmp = "clings_io3.tmp";
    Point p = {.x = 3, .y = -7};
    Point q = {.x = 0, .y = 0};

    CHECK(sauver_point(tmp, &p) == 0);
    CHECK(charger_point(tmp, &q) == 0);
    CHECK(q.x == 3 && q.y == -7);

    CHECK(charger_point("/aucun/fichier/ici", &q) == -1);

    remove(tmp);
    OK("fichier binaire");
    return 0;
}
