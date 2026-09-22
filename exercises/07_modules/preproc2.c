// Le préprocesseur travaille sur du TEXTE, avant même que le compilateur ne
// voie le code. L'opérateur `#` transforme son argument en chaîne :
//
//   #define STR(x) #x
//   STR(bonjour)          ->   "bonjour"
//
// Mais `#` empêche l'argument d'être développé : si `VERSION` vaut 3,
// `STR(VERSION)` donne "VERSION", pas "3". Pour développer d'abord, on passe
// par une seconde macro intermédiaire.
//
// Corrige `STR`, puis écris `XSTR` sur ce modèle.


// I AM NOT DONE

#include <string.h>
#include "clings.h"

#define STR(x) x
#define XSTR(x) x

#define VERSION 3

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(strcmp(STR(bonjour), "bonjour") == 0);
    CHECK(strcmp(XSTR(VERSION), "3") == 0);
    OK("stringification");
    return 0;
}
