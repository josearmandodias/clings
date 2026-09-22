#include <stddef.h>
#include <stdio.h>
#include "clings.h"

int ecrire_nombres(const char *chemin, const int *tab, size_t n)
{
    FILE *f = fopen(chemin, "w");
    if (!f) return -1;

    for (size_t i = 0; i < n; i++) {
        if (fprintf(f, "%d\n", tab[i]) < 0) {
            fclose(f);
            return -1;
        }
    }

    if (fclose(f) != 0) return -1;
    return 0;
}

int relire_somme(const char *chemin, long *somme)
{
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;

    long total = 0;
    int v;
    while (fscanf(f, "%d", &v) == 1) {
        total += v;
    }

    fclose(f);
    if (somme) *somme = total;
    return 0;
}

int main(void)
{
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
