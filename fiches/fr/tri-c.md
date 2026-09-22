# Les tris en C — fiche

Trier, c'est réorganiser un tableau selon un ordre. Les quatre algorithmes de
cette section montrent quatre stratégies — insertion, fusion, partition, comptage
— et sont l'occasion de comparer coûts et stabilité. Cette fiche accompagne le
chapitre `12_tri`.

## Vocabulaire

- **en place** : n'utilise qu'une quantité constante de mémoire en plus du tableau ;
- **stable** : préserve l'ordre relatif des éléments égaux ;
- **complexité** : le nombre d'opérations en fonction de `n`, dans le pire cas ou
  en moyenne.

## Tri par insertion

On construit une partie triée au début : on prend l'élément suivant et on le fait
remonter à sa place en décalant les plus grands vers la droite.

```c
void tri_insertion(int *tab, size_t n)
{
    for (size_t i = 1; i < n; i++) {
        int cle = tab[i];
        size_t j = i;
        while (j > 0 && tab[j - 1] > cle) {
            tab[j] = tab[j - 1];
            j--;
        }
        tab[j] = cle;
    }
}
```

`O(n^2)` dans le pire cas, `O(n)` sur un tableau déjà trié, stable et en place.
Excellent sur les petits tableaux. C'est `tri1`.

## Tri par fusion (diviser/régner)

Couper en deux, trier chaque moitié récursivement, puis **fusionner** deux suites
triées en une seule. La fusion a besoin d'un tampon, alloué **une seule fois**
avant de commencer.

```c
static void fusion(int *tab, int *tmp, size_t debut, size_t milieu, size_t fin)
{
    size_t i = debut, j = milieu, k = debut;
    while (i < milieu && j < fin)
        tmp[k++] = tab[i] <= tab[j] ? tab[i++] : tab[j++];
    while (i < milieu) tmp[k++] = tab[i++];
    while (j < fin)    tmp[k++] = tab[j++];
    for (i = debut; i < fin; i++) tab[i] = tmp[i];
}
```

`O(n log n)` garanti, stable, mais `O(n)` d'espace supplémentaire. C'est `tri2`.

## Tri rapide et partition de Lomuto

On choisit un pivot (ici le dernier), on place à gauche les plus petits et à
droite les plus grands, puis on trie chaque côté.

```c
static size_t partition(int *tab, size_t debut, size_t fin)
{
    int pivot = tab[fin - 1];
    size_t i = debut;
    for (size_t j = debut; j + 1 < fin; j++) {
        if (tab[j] <= pivot) {
            echanger(&tab[i], &tab[j]);
            i++;
        }
    }
    echanger(&tab[i], &tab[fin - 1]);   // le pivot rejoint sa place
    return i;
}
```

`O(n log n)` en moyenne, `O(n^2)` si les pivots sont systématiquement extrêmes, en
place et **non stable**. C'est `tri3`.

## Tri par comptage

Aucune comparaison : on compte les occurrences de chaque valeur (entre `0` et
`max`), puis on réécrit le tableau dans l'ordre.

```c
void tri_comptage(int *tab, size_t n, int max)
{
    if (n == 0) return;
    int *compte = calloc((size_t)max + 1, sizeof *compte);
    if (compte == NULL) return;
    for (size_t i = 0; i < n; i++) compte[tab[i]]++;
    size_t k = 0;
    for (int v = 0; v <= max; v++)
        while (compte[v]-- > 0) tab[k++] = v;
    free(compte);
}
```

`O(n + max)` : très rapide si la plage de valeurs est petite, gaspilleur sinon. Il
suppose que toutes les valeurs sont dans `[0, max]`. C'est `tri4`.

## Comparer

| Tri | Meilleur | Moyen | Pire | Espace | Stable | En place |
|---|---|---|---|---|---|---|
| Insertion | O(n) | O(n²) | O(n²) | O(1) | oui | oui |
| Fusion | O(n log n) | O(n log n) | O(n log n) | O(n) | oui | non |
| Rapide | O(n log n) | O(n log n) | O(n²) | O(log n) | non | oui |
| Comptage | O(n + k) | O(n + k) | O(n + k) | O(k) | — | non |

`k` désigne la plage des valeurs (`max + 1`). Le « pire » du tri rapide arrive
quand le pivot est toujours le plus petit ou le plus grand — par exemple sur un
tableau déjà trié avec le pivot en dernier (son espace de pile monte alors à
`O(n)`). La stabilité du tri par comptage ne se voit que dans la variante à
comptage cumulé : celle de `tri4` ne range que des entiers, où elle est sans effet
observable.

## `qsort` et le comparateur

La bibliothèque fournit `qsort` (souvent un tri rapide amélioré). Tu lui donnes la
taille d'un élément et une comparaison.

```c
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);     // -1, 0 ou +1 sans soustraction qui déborde
}

qsort(tab, n, sizeof tab[0], cmp_int);
```

`(x > y) - (x < y)` renvoie exactement `-1`, `0` ou `1`. Le comparateur doit
définir un ordre **total** : s'il est incohérent (par exemple `a - b` qui
déborde), `qsort` peut mal se comporter. C'est `structs3` et `structs8` dans la
section `06_structs`.

## Recherche binaire sur un tableau trié

Une fois le tableau trié, on cherche en `O(log n)` :

```c
int recherche_binaire(const int *tab, size_t n, int cible)
{
    size_t debut = 0, fin = n;                  // [debut, fin)
    while (debut < fin) {
        size_t milieu = debut + (fin - debut) / 2;
        if (tab[milieu] == cible) return (int)milieu;
        if (tab[milieu] < cible) debut = milieu + 1;
        else                     fin = milieu;
    }
    return -1;
}
```

Elle **exige** un tableau trié ; sur un tableau désordonné, elle ne conclut rien.

## Le réflexe

Choisis ton tri selon trois questions : **la plage des valeurs est-elle petite**
(comptage), **faut-il garantir le pire cas** (fusion), **la stabilité
compte-t-elle** (fusion, insertion). Et retiens qu'un tableau trié ouvre la porte
à la recherche binaire.

Exercices liés : `tri1`..`tri4`.
