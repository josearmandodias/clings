# Modules, headers et préprocesseur — fiche

Un programme C se compile **fichier par fichier**. Chaque `.c` est traduit
isolément en une *unité de traduction*, sans rien savoir des autres ; c'est
l'éditeur de liens qui rassemble ensuite le tout. Cette fiche accompagne le
chapitre `07_modules`.

## Compilation séparée

```sh
cc -std=c17 -Wall -Wextra -Werror -g -c math.c -o math.o
cc -std=c17 -Wall -Wextra -Werror -g -c main.c -o main.o
cc math.o main.o -o prog
```

- `-c` compile sans lier : produit un fichier objet `.o` ;
- la dernière commande lie les objets et les bibliothèques.

Chaque `.c` compile à l'aveugle. Si `main.c` appelle `carre`, le compilateur doit
connaître sa **déclaration**, sinon erreur « implicit declaration ». C'est le
rôle du header.

## Déclaration vs définition

```c
int carre(int x);                     // déclaration : une promesse
int carre(int x) { return x * x; }    // définition : le code
```

Une déclaration dit l'**existence** et le type ; une définition fournit le
**corps** (ou le stockage). Une fonction peut être déclarée cent fois, définie une
seule. Le header contient les déclarations. C'est `modules1` et `modules2`.

## Headers et gardes d'inclusion

```c
/* math.h */
#ifndef MATH_H
#define MATH_H

int carre(int x);
int cube(int x);

#endif /* MATH_H */
```

Sans garde, inclure deux fois le même header redéclarerait tout. La garde est ce
`#ifndef` / `#define` / `#endif` ; `#pragma once` est répandu mais non standard.

On inclut les headers du projet avec des guillemets (`#include "math.h"`, cherché
d'abord dans le dossier courant) et ceux du système avec `<...>`
(`#include <stdio.h>`).

## `static` et `extern`

| Mot-clé | Effet |
|---|---|
| `static` sur une fonction ou une globale | visible **uniquement dans le fichier** (« privé ») |
| `static` sur une variable locale | garde sa valeur entre les appels, une seule instance |
| `extern` sur une variable | déclare une variable définie ailleurs |
| `extern` sur une fonction | rappel d'un prototype externe (souvent implicite) |

`static` sur une fonction résout les conflits de noms entre deux fichiers qui
définissent chacune leur `carre`. C'est le « private » du C.

```c
static int appels;      // compteur privé à ce fichier
```

## `#define` et macros

Le préprocesseur fait du **remplacement de texte**, avant toute compilation.

```c
#define PI 3.14159
#define TAILLE 128

#define CARRE(x) ((x) * (x))            // parenthèse TOUT
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

Sans parenthèses, `CARRE(1 + 2)` devient `1 + 2 * 1 + 2`, soit 5. Les parenthèses
autour de **chaque paramètre** et du **résultat** sont obligatoires. C'est
`preproc1`.

Convention : noms de macros en majuscules. Et pour tout ce qui a un type,
préfère une fonction `static` (ou `static inline`) : ni surprise de précédence,
ni double évaluation.

## Le piège de la double évaluation

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
MAX(i++, j)     // i est incrémenté une ou deux fois selon le cas
```

Le paramètre est du texte recopié : il apparaît plusieurs fois dans l'expansion.
Une fonction, elle, évalue ses arguments une seule fois. C'est la raison pour
laquelle `preproc1` finit par demander une vraie fonction `max`.

## `#` (stringify) et `##` (concat)

```c
#define STR(x)  #x          // argument -> chaîne : STR(a) -> "a"
#define CONCAT(a, b) a##b   // colle deux jetons : CONCAT(mon_, test) -> mon_test
```

`#` et `##` empêchent leurs arguments d'être développés : si `VERSION` vaut `3`,
`STR(VERSION)` donne `"VERSION"`, pas `"3"`. Pour développer d'abord, on passe par
une macro intermédiaire :

```c
#define STR(x)  #x
#define XSTR(x) STR(x)      // XSTR(VERSION) -> "3"
```

C'est `preproc2` et `preproc3`.

## Compilation conditionnelle

```c
#if NIVEAU == 1
    return "debutant";
#elif NIVEAU == 2
    return "intermediaire";
#else
    return "expert";
#endif

#ifdef DEBUG
    fprintf(stderr, "valeur = %d\n", v);
#endif
```

`#if` évalue des constantes **connues du préprocesseur** (et `defined(X)`) ;
`#ifdef` teste si un nom est défini (`-DDEBUG` en ligne de commande). Le code
écarté n'est même pas compilé. À réserver à la plateforme ou aux diagnostics, pas
à la logique métier. C'est `preproc4`.

## Le réflexe

Une unité de traduction ne voit que ce qu'on lui déclare : **le header dit quoi**,
**le `.c` dit comment**, **la garde empêche la redite**. Et pour les macros :
parenthèse tout, ou écris une fonction.

Exercices liés : `modules1`, `modules2`, `preproc1`..`preproc4`.
