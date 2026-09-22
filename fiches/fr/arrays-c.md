# Les tableaux en C — fiche

Un tableau C est un bloc **contigu** d'éléments du même type, sans longueur
stockée et sans contrôle de bornes. Comprendre ces trois faits règle la majorité
des exercices de la section. Cette fiche accompagne le chapitre `03_arrays`.

## Déclarer et initialiser

```c
int a[5];                  // 5 int non initialisés
int b[5] = {1, 2, 3, 4, 5};
int c[5] = {1, 2};         // {1, 2, 0, 0, 0} : le reste est remis à zéro
int d[5] = {0};            // tout à zéro, l'idiome à retenir
int e[]  = {1, 2, 3};      // taille déduite : 3
```

Une initialisation partielle remplit le reste avec des zéros. Une variable
**locale non initialisée**, elle, contient n'importe quoi : ne la lis jamais
avant de l'avoir écrite.

## `sizeof` et la décroissance

Là où le tableau est déclaré, `sizeof` donne sa taille totale. Passé à une
fonction, il **décroît** (decay) en pointeur sur son premier élément : la
longueur est perdue.

```c
int tab[5];
sizeof(tab) / sizeof(tab[0])   // 5, ici seulement

void f(int *tab) {
    sizeof(tab);   // 8 : la taille d'un pointeur, pas du tableau
}
```

D'où la règle : **toute fonction qui reçoit un tableau reçoit aussi sa longueur**.

```c
int somme(const int *tab, size_t n)
{
    int total = 0;
    for (size_t i = 0; i < n; i++) {
        total += tab[i];
    }
    return total;
}
```

Le `const` promet qu'on ne modifie pas les éléments. C'est `arrays1`.

## Les bornes

Les indices valides vont de `0` à `n - 1`. Le C ne vérifie rien : écrire
`tab[n]` écrase la mémoire voisine.

```c
#define N 10
int tab[N];
for (int i = 0; i < N; i++) {   // PAS <=
    tab[i] = i * i;
}
```

ASan signale `stack-buffer-overflow` et donne l'adresse fautive. Apprendre à
lire ce rapport est justement le but de `arrays2`.

## Tableaux à deux dimensions

`int m[3][4]` est un bloc de 12 `int`, rangées contiguës : ce ne sont pas des
listes de pointeurs.

```
m[i][j]  ==  *(base + i * 4 + j)      // 4 = nombre de colonnes
```

L'ordre est « ligne majeure » (row-major) : `m[0][3]` est immédiatement suivi de
`m[1][0]`. Passer un 2D à une fonction oblige à fixer le nombre de colonnes :

```c
void remplir(int m[3][4]);                    // équivaut à int (*m)[4]
void transpose(const int e[3][4], int s[4][3]);
```

C'est `arrays3` et `arrays8` (produit matriciel : trois boucles imbriquées).

## Parcours et premier maximum

On garde le meilleur candidat et on le met à jour. Pour le **premier** maximum,
on ne remplace que sur `>` strict, jamais sur `>=`.

```c
size_t index_max(const int *tab, size_t n)
{
    size_t best = 0;
    for (size_t i = 1; i < n; i++) {
        if (tab[i] > tab[best]) {
            best = i;
        }
    }
    return best;
}
```

C'est `arrays4`.

## Inverser en place

Deux indices qui se rapprochent, un temporaire, et on s'arrête au milieu.

```c
void inverser(int *tab, size_t n)
{
    for (size_t i = 0; i < n / 2; i++) {
        int tmp = tab[i];
        tab[i] = tab[n - 1 - i];
        tab[n - 1 - i] = tmp;
    }
}
```

`n / 2` couvre les tailles paires et impaires. C'est `arrays5`.

## Rotation à gauche

Faire tourner de `k` vers la gauche amène `tab[k]` en tête. On ramène d'abord `k`
dans `[0, n)`. Trois inversions suffisent, sans tableau annexe :

```c
void rotation_gauche(int *tab, size_t n, size_t k)
{
    if (n == 0) return;          // sinon k %= n divise par zéro
    k %= n;
    inverser(tab, k);
    inverser(tab + k, n - k);
    inverser(tab, n);
}
```

`{1, 2, 3, 4, 5}` avec `k = 2` donne `{3, 4, 5, 1, 2}`. C'est `arrays6`.

## Recherche binaire

Sur un tableau **trié**, on élimine la moitié des candidats à chaque étape.
L'intervalle semi-ouvert `[debut, fin)` évite les cas particuliers.

```c
int recherche_binaire(const int *tab, size_t n, int cible)
{
    size_t debut = 0, fin = n;             // [debut, fin)
    while (debut < fin) {
        size_t milieu = debut + (fin - debut) / 2;
        if (tab[milieu] == cible) return (int)milieu;
        if (tab[milieu] < cible)  debut = milieu + 1;
        else                      fin = milieu;
    }
    return -1;
}
```

Calcule le milieu avec `debut + (fin - debut) / 2` plutôt que `(debut + fin) / 2`,
pour éviter tout débordement sur de grands indices. C'est `arrays7`.

## `memcpy` et `memmove`

`memcpy(dst, src, n)` copie `n` octets ; `memmove` fait pareil mais autorise le
**recouvrement**. Pour retirer un élément en décalant la suite, source et
destination se chevauchent : c'est donc `memmove`.

```c
void supprimer(int *tab, size_t *n, size_t pos)
{
    memmove(tab + pos, tab + pos + 1, (*n - pos - 1) * sizeof *tab);
    (*n)--;
}
```

Utiliser `memcpy` là où il y a recouvrement est un comportement indéfini ;
ASan parle de `memcpy-param-overlap`. C'est `arrays9`.

## Le réflexe

Devant un tableau, trois questions : **qui connaît sa longueur**, **les indices
vont-ils bien de `0` à `n-1`**, **les zones copiées se recouvrent-elles**. Trois
questions, trois bugs évités.

Exercices liés : `arrays1`..`arrays9`.
