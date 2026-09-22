// Lire un fichier ligne par ligne, la version portable et sûre.
//
// fgets(buf, taille, f) lit au plus taille-1 caractères, garde le '\n' s'il
// tient, et renvoie NULL en fin de fichier. Il ne peut pas déborder — à la
// différence de gets(), retiré du langage en 2011.
//
// Complète `compter_lignes` : ouvre le fichier, compte les lignes, ferme.
// Renvoie -1 si le fichier ne s'ouvre pas.


// I AM NOT DONE

#include <stdio.h>
#include "clings.h"

int compter_lignes(const char *chemin)
{
    /* TODO */
    (void)chemin;
    return -1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
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
