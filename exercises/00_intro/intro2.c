// Le compilateur est ton premier professeur : il indique la ligne et la
// raison d'un problème. Apprends à lire ses messages de haut en bas.
//
// Ce programme additionne deux nombres et calcule leur moyenne. Il contient
// exactement trois fautes ; corrige-les une à une, en recompilant à chaque
// fois pour voir le message suivant disparaître.
//
//   1. une instruction qui ne se termine pas correctement ;
//   2. une variable utilisée sans avoir été déclarée ;
//   3. un format d'affichage qui ne correspond pas au type affiché.


// I AM NOT DONE

#include <stdio.h>
#include "clings.h"

int main(void)
{
    int a = 19;
    int b = 23
    somme = a + b;
    double moyenne = somme / 2.0;

    printf("somme = %d, moyenne = %d\n", somme, moyenne);

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(somme == 42);
    OK("message de compilation lu");
    return 0;
}
