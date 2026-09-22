// Pour un fichier texte, on écrit et on relit avec les mêmes formats que
// printf/scanf : fprintf vers un FILE*, fscanf depuis un FILE*. Un entier
// par ligne donne un format simple et lisible.
//
// `ecrire_nombres` écrit les `n` entiers de `tab`, un par ligne, et renvoie 0
// (ou -1 si le fichier ne s'ouvre pas). `relire_somme` relit tous les entiers
// du fichier et range leur somme dans `*somme`, en renvoyant 0 (ou -1 si
// l'ouverture échoue).


// I AM NOT DONE

#include <stddef.h>
#include <stdio.h>
#include "clings.h"

int ecrire_nombres(const char *chemin, const int *tab, size_t n)
{
    /* TODO */
    (void)chemin;
    (void)tab;
    (void)n;
    return -1;
}

int relire_somme(const char *chemin, long *somme)
{
    /* TODO */
    (void)chemin;
    (void)somme;
    return -1;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    const char *tmp = "clings_io2.tmp";
    const int tab[] = {3, 5, 7};
    long somme = -1;

    CHECK(ecrire_nombres(tmp, tab, 3) == 0);
    CHECK(relire_somme(tmp, &somme) == 0 && somme == 15);

    CHECK(ecrire_nombres(tmp, tab, 0) == 0);
    CHECK(relire_somme(tmp, &somme) == 0 && somme == 0);

    CHECK(relire_somme("/aucun/fichier/ici", &somme) == -1);

    remove(tmp);
    OK("écriture et relecture de nombres");
    return 0;
}
