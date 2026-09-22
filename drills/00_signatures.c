/* drills/00_signatures.c — lire un contrat, ecrire une signature.
 *
 * Six contrats ecrits en francais. A toi d'ecrire la signature juste :
 * type de chaque parametre, emplacement des `const`, `[]`, `*`, `size_t`.
 *
 * Regles du jeu :
 *   - tu ne modifies QUE les lignes marquees `SIGNATURE` ;
 *   - les corps (sous `NE TOUCHE PAS`) et les appels de `main` sont figes :
 *     ce sont eux qui definissent l'exercice ;
 *   - le fichier doit compiler avec zero erreur ET zero warning.
 *
 * Verifier :
 *     cc -std=c17 -Wall -Wextra -Werror -Wshadow -g -Iinclude \
 *        drills/00_signatures.c -o /tmp/signatures && /tmp/signatures
 *
 * Pour un aller-retour plus rapide (pas de binaire, juste les types) :
 *     cc -std=c17 -Wall -Wextra -Werror -Wshadow -fsyntax-only \
 *        -Iinclude drills/00_signatures.c
 *
 * Le compilateur est le seul juge. Et quand un type te resiste, il peut
 * aussi te le dire : voir l'astuce de l'oracle en bas de fichier.
 */

#include <stddef.h>
#include "clings.h"

/* ------------------------------------------------------------------ 1/6
 * `lire_entier` lit un entier dans une chaine. Elle ne modifie pas la
 * chaine, mais elle ecrit son resultat dans un `long` de l'appelant.
 * Renvoie 0 si tout va bien, -1 sinon.
 */

int lire_entier(const char *s, long *out)   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    if (s[0] == '\0') {
        return -1;
    }
    if (out != NULL) {
        *out = 0;
    }
    return 0;
}

/* ------------------------------------------------------------------ 2/6
 * `moyenne` calcule la moyenne d'une serie d'`int`. Elle ne modifie pas
 * la serie, qui peut donc etre en lecture seule, et elle a besoin de sa
 * longueur — la forme idiomatique d'une longueur en C, c'est `size_t`.
 */

double moyenne(const int *t, size_t n)   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    if (n == 0) {
        return 0.0;
    }
    long total = 0;
    for (size_t i = 0; i < n; i++) {
        total += t[i];
    }
    return (double)total / (double)n;
}

/* ------------------------------------------------------------------ 3/6
 * `somme_matrice` additionne les 12 elements d'une matrice d'`int` de
 * 3 lignes sur 4 colonnes. Elle ne la modifie pas.
 */

long somme_matrice(const int m[3][4])   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    long total = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            total += m[i][j];
        }
    }
    return total;
}

/* ------------------------------------------------------------------ 4/6
 * `incr` incremente l'`int` de l'appelant et renvoie l'ancienne valeur.
 */

int incr(int *n)   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    int ancien = *n;
    (*n)++;
    return ancien;
}

/* ------------------------------------------------------------------ 5/6
 * `dernier` renvoie l'adresse du dernier element d'une serie d'`int`.
 * Ni elle ni l'appelant ne doivent pouvoir modifier la serie a travers
 * ce pointeur.
 */

const int *dernier(const int *t, size_t n)   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    return &t[n - 1];
}

/* ------------------------------------------------------------------ 6/6
 * `afficher_etiquettes` affiche un tableau de chaines. Elle ne modifie
 * ni les caracteres des chaines, ni les pointeurs du tableau. L'appelant
 * peut donc lui passer un tableau dont les pointeurs sont eux-memes
 * constants (`static const char *const[]`).
 */

void afficher_etiquettes(const char *const*e, size_t n)   /* SIGNATURE */
{
    /* NE TOUCHE PAS */
    for (size_t i = 0; i < n; i++) {
        printf("      %s\n", e[i]);
    }
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    static const char *const source = "123";
    long v = 12345;
    CHECK(lire_entier(source, &v) == 0);
    CHECK(v == 0);

    static const int notes[] = {12, 15, 9};
    CHECK(moyenne(notes, sizeof notes / sizeof *notes) == 12.0);

    static const int identite[3][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
    };
    CHECK(somme_matrice(identite) == 3);

    int compteur = 1;
    CHECK(incr(&compteur) == 1);
    CHECK(compteur == 2);

    static const int serie[] = {4, 8, 15, 16, 23, 42};
    const int *p = dernier(serie, sizeof serie / sizeof *serie);
    CHECK(p == &serie[5]);
    CHECK(*p == 42);

    static const char *const etiquettes[] = {"alpha", "beta"};
    afficher_etiquettes(etiquettes, sizeof etiquettes / sizeof *etiquettes);

    OK("les six signatures sont justes");
    return 0;
}

/* --------------------------------------------------------------- ORACLE
 *
 * Pour faire dire a clang le type exact d'une declaration qui te resiste,
 * ajoute temporairement cette ligne DANS main, compile, lis l'erreur,
 * puis supprime-la :
 *
 *     int (*oracle)(void) = lire_entier;
 *
 * clang repondra par exemple :
 *
 *     error: incompatible pointer types initializing 'int (*)(void)' with
 *     an expression of type 'int (*)(const char *, long *)'
 *
 * et il ne reste plus qu'a traduire ce type en ecriture de declaration.
 */
