#include <stdio.h>
#include "clings.h"

int compter_lignes(const char *chemin)
{
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;

    int  n = 0;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        n++;
    }
    fclose(f);
    return n;
}

int main(void)
{
    const char *tmp = "clings_io1.tmp";
    FILE *f = fopen(tmp, "w");
    CHECK(f != NULL);
    fputs("une\ndeux\ntrois\n", f);
    fclose(f);

    CHECK(compter_lignes(tmp) == 3);
    CHECK(compter_lignes("/aucun/fichier/ici") == -1);

    const char *tmp_vide = "clings_io1_vide.tmp";
    FILE *fv = fopen(tmp_vide, "w");
    CHECK(fv != NULL);
    fclose(fv);
    CHECK(compter_lignes(tmp_vide) == 0);      /* fichier vide : zero ligne */
    remove(tmp_vide);

    const char *tmp_part = "clings_io1_part.tmp";
    FILE *fp = fopen(tmp_part, "w");
    CHECK(fp != NULL);
    fputs("alpha", fp);                        /* pas de '\n' final */
    fclose(fp);
    CHECK(compter_lignes(tmp_part) == 1);
    remove(tmp_part);

    remove(tmp);
    OK("lecture de fichier");
    return 0;
}
