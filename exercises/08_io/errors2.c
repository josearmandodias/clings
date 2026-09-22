// fseek(f, 0, SEEK_END) place le curseur à la fin du fichier, et ftell(f)
// renvoie la position courante : le nombre d'octets du fichier. C'est ainsi
// qu'on mesure une taille.
//
// `taille_fichier` renvoie 0 et écrit la taille dans `*taille`, ou renvoie -1
// en laissant `errno` tel que l'échec de `fopen` l'a positionné. On ne lit
// `errno` qu'après un appel qui a signalé une erreur.


// I AM NOT DONE

#include <errno.h>
#include <stdio.h>
#include "clings.h"

int taille_fichier(const char *chemin, long *taille)
{
    /* TODO */
    (void)chemin;
    (void)taille;
    return -1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    const char *tmp = "clings_errors2.tmp";
    FILE *f = fopen(tmp, "wb");
    CHECK(f != NULL);
    fputs("abcdef", f);
    fclose(f);

    long taille = -1;
    CHECK(taille_fichier(tmp, &taille) == 0);
    CHECK(taille == 6);

    errno = 0;
    CHECK(taille_fichier("/aucun/fichier/ici", &taille) == -1);
    CHECK(errno == ENOENT);

    remove(tmp);
    OK("errno et taille de fichier");
    return 0;
}
