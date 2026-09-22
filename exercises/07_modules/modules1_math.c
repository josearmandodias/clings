/* Implémentation. Note le `static` : la variable est visible uniquement
 * dans ce fichier. C'est le "private" du C. */

#include "modules1_math.h"

static int appels = 0;

int carre(int x)
{
    appels++;
    return x * x;
}

int cube(int x)
{
    appels++;
    return x * x * x;
}

int compteur_appels(void)
{
    return appels;
}
