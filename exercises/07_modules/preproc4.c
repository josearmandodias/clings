// `#if`, `#elif`, `#else` et `#endif` choisissent le code compilé selon des
// constantes connues du préprocesseur. C'est ainsi qu'on adapte un programme
// à une plateforme, ou qu'on active des diagnostics de mise au point.
//
// En t'aidant de la constante `NIVEAU`, écris `nom_niveau` pour qu'elle
// renvoie "debutant" si NIVEAU vaut 1, "intermediaire" si NIVEAU vaut 2, et
// "expert" sinon. Le choix doit être fait à la compilation, avec #if/#elif,
// pas par un `if` à l'exécution.
//
// Bonus : entoure un affichage de mise au point d'un bloc `#ifdef DEBUG`,
// qui ne doit rien produire en compilation normale (sans -DDEBUG).


// I AM NOT DONE

#include <stdio.h>
#include <string.h>
#include "clings.h"

#define NIVEAU 2

const char *nom_niveau(void)
{
    /* TODO */
    return NULL;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(nom_niveau(), "intermediaire") == 0);
    OK("compilation conditionnelle");
    return 0;
}
