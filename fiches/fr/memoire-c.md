# La mémoire en C — fiche

En C, deux zones se partagent le travail : la **pile** (automatique, courte
durée) et le **tas** (alloué à la demande, libéré à la main). La question
centrale n'est pas « comment allouer » mais **qui possède le bloc et quand le
libérer**. Cette fiche accompagne le chapitre `05_memory`.

## Pile vs tas

```c
int  local[10];                        // pile : détruit au retour de la fonction
int *tas = malloc(10 * sizeof *tas);   // tas : vit jusqu'au free
```

| | Pile | Tas |
|---|---|---|
| Durée de vie | le bloc d'appel | jusqu'au `free` |
| Taille | limitée, fixe | grande, à la demande |
| Vitesse | très rapide | plus lente |
| Libération | automatique | manuelle |

Renvoyer l'adresse d'une variable locale donne un **dangling pointer** : la
mémoire est recyclée dès que la fonction rend la main. Si la donnée doit
survivre, elle doit venir du tas. C'est `memory1`.

## `malloc`, `calloc`, `realloc`, `free`

```c
#include <stdlib.h>

void *p = malloc(n * sizeof *p);        // n éléments, non initialisés
void *q = calloc(n, sizeof *q);         // n éléments, remis à zéro
void *r = realloc(p, m * sizeof *p);    // redimensionne (peut déplacer)
free(r);
```

- `malloc` renvoie `NULL` en cas d'échec : teste toujours ;
- `calloc(n, taille)` remet à zéro **et** vérifie lui-même que `n * taille` ne
  déborde pas ;
- `realloc(NULL, n)` se comporte comme `malloc(n)` ; `realloc(p, 0)` libère le
  bloc (ou renvoie `NULL` selon l'implémentation).

Écris `sizeof *p`, pas `sizeof(int)` : l'expression reste juste si le type
change.

## La garde anti-débordement

Avant un `malloc(n * sizeof *p)`, vérifie que la multiplication tient dans un
`size_t` :

```c
#include <stdint.h>
if (n == 0 || n > SIZE_MAX / sizeof(int)) {
    return NULL;                 // une fois le produit débordé, c'est trop tard
}
int *t = calloc(n, sizeof(int));
```

`SIZE_MAX` vient de `<stdint.h>`. La garde se place **avant** la multiplication.
C'est `memory6`.

## Fuites, use-after-free, double free

| Faute | Ce qui se passe | Ce que dit l'outil |
|---|---|---|
| Oublier `free` | la mémoire croît sans fin | `CHECK_NO_LEAK` / LeakSanitizer |
| Lire après `free` | valeur incohérente | `heap-use-after-free` |
| `free` deux fois | l'allocateur est corrompu | `double-free` |
| Renvoyer une locale | pointeur mort | `stack-use-after-return` |

Trois réflexes :

1. libérer le plus tard possible, à **un seul endroit** ;
2. mettre le pointeur à `NULL` juste après le `free` ;
3. vérifier que chaque `malloc` a exactement un propriétaire.

```c
free(p);
p = NULL;          // free(NULL) ne fait rien : c'est inoffensif
```

C'est `memory2`, `memory3` et `memory4`.

## Propriété et copie profonde

Copier une struct (`*c = *p`) recopie les pointeurs, pas ce qu'ils désignent : les
deux pointent alors sur la **même** chaîne. Pour un vrai clone, il faut dupliquer
les octets.

```c
Personne *personne_clone(const Personne *p)
{
    Personne *c = malloc(sizeof *c);
    if (c == NULL) return NULL;
    c->age = p->age;
    c->nom = malloc(strlen(p->nom) + 1);      // pas d'oubli du + 1
    if (c->nom == NULL) { free(c); return NULL; }
    strcpy(c->nom, p->nom);
    return c;
}
```

Libère la copie partielle si la seconde allocation échoue. C'est `memory10`.

## Tableau dynamique qui grandit

Doubler la capacité donne un coût amorti constant par ajout
(0 -> 4 -> 8 -> 16...). Avec `realloc`, passe toujours par un **temporaire** :

```c
size_t nc = v->capacite ? v->capacite * 2 : 4;
int *tmp = realloc(v->data, nc * sizeof *tmp);
if (tmp == NULL) return 0;        // v->data reste intact
v->data = tmp;
v->capacite = nc;
v->data[v->taille++] = valeur;
return 1;
```

Écrire `v->data = realloc(v->data, ...)` perdrait le bloc d'origine si `realloc`
échoue. C'est `memory5` et `memory8`.

## Matrice dynamique

Deux niveaux d'allocation : le tableau de pointeurs (les lignes), puis chaque
ligne.

```c
int **creer_matrice(size_t lignes, size_t colonnes)
{
    int **m = malloc(lignes * sizeof *m);
    if (m == NULL) return NULL;
    for (size_t i = 0; i < lignes; i++) {
        m[i] = malloc(colonnes * sizeof *m[i]);
        if (m[i] == NULL) {
            liberer_matrice(m, i);     // libère seulement ce qui est alloué
            return NULL;
        }
    }
    return m;
}
```

Sur le chemin d'erreur, libère ce qui précède : pas de fuite même quand tout ne
réussit pas. C'est `memory7`.

## Libérer une structure qui possède

L'ordre compte : d'abord ce que la structure **possède**, puis la structure
elle-même.

```c
void personne_liberer(Personne *p)
{
    if (p == NULL) return;
    free(p->nom);   // la chaîne d'abord
    free(p);        // puis la coquille
}
```

C'est `memory9` et `memory11` (libérer sur **tous** les chemins de sortie, pas
seulement le chemin nominal).

## Le réflexe

Pour chaque bloc, trois questions : **d'où vient-il**, **jusqu'à quand est-il
valide**, **qui le libère**. Un `malloc` sans propriétaire est une fuite ; un
`free` sans propriétaire est un double free.

Exercices liés : `memory1`..`memory11`.
