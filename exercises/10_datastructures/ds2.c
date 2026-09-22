// Une file (queue) est une structure FIFO : le premier entre est le premier
// sorti. Avec un tampon fixe, on reutilise les cases laissees libres par les
// depilages : les indices reviennent au debut grace a un modulo.
//
// `tete` est l'indice du premier element, `taille` le nombre d'elements.
// Complete `file_push` (0 si pleine) et `file_pop` (0 si vide).


// I AM NOT DONE

#include "clings.h"

#define CAP 4

typedef struct {
    int    data[CAP];
    size_t tete;
    size_t taille;
} File;

int file_push(File *f, int v)
{
    /* TODO */
    (void)f;
    (void)v;
    return 0;
}

int file_pop(File *f, int *v)
{
    /* TODO */
    (void)f;
    (void)v;
    return 0;
}

int main(void)
{
    File f = {{0}, 0, 0};
    int  v = 0;

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(file_pop(&f, &v) == 0);   /* file vide */

    CHECK(file_push(&f, 10) == 1);
    CHECK(file_push(&f, 20) == 1);
    CHECK(file_push(&f, 30) == 1);
    CHECK(file_push(&f, 40) == 1);
    CHECK(file_push(&f, 50) == 0);  /* pleine */
    CHECK(f.taille == (size_t)CAP);

    CHECK(file_pop(&f, &v) == 1 && v == 10);   /* FIFO */
    CHECK(file_pop(&f, &v) == 1 && v == 20);

    /* apres deux depilages, les indices doivent boucler */
    CHECK(file_push(&f, 50) == 1);
    CHECK(file_push(&f, 60) == 1);
    CHECK(file_push(&f, 70) == 0);  /* pleine de nouveau */

    CHECK(file_pop(&f, &v) == 1 && v == 30);
    CHECK(file_pop(&f, &v) == 1 && v == 40);
    CHECK(file_pop(&f, &v) == 1 && v == 50);
    CHECK(file_pop(&f, &v) == 1 && v == 60);
    CHECK(file_pop(&f, &v) == 0);

    OK("file circulaire");
    return 0;
}
