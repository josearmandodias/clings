#include <errno.h>
#include <stdio.h>
#include "clings.h"

int taille_fichier(const char *chemin, long *taille)
{
    FILE *f = fopen(chemin, "rb");
    if (!f) return -1;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -1;
    }

    long t = ftell(f);
    if (t < 0) {
        fclose(f);
        return -1;
    }

    fclose(f);
    if (taille) *taille = t;
    return 0;
}

int main(void)
{
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
