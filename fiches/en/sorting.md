# Sorting in C — cheat sheet

Sorting means rearranging an array according to an order. The four algorithms of
this section show four strategies — insertion, merge, partition, counting
— and are an opportunity to compare costs and stability. This cheat sheet accompanies the
`12_tri` chapter.

## Vocabulary

- **in place**: uses only a constant amount of extra memory beyond the array;
- **stable**: preserves the relative order of equal elements;
- **complexity**: the number of operations as a function of `n`, in the worst case or
  on average.

## Insertion sort

We build a sorted part at the beginning: we take the next element and make it
move up to its place by shifting the larger ones to the right.

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

`O(n^2)` in the worst case, `O(n)` on an already sorted array, stable and in place.
Excellent on small arrays. This is `tri1`.

## Merge sort (divide and conquer)

Cut in two, sort each half recursively, then **merge** two sorted
sequences into one. The merge needs a buffer, allocated **once**
before starting.

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

`O(n log n)` guaranteed, stable, but `O(n)` extra space. This is `tri2`.

## Quicksort and Lomuto partition

We choose a pivot (here the last one), place the smaller ones on the left and
the larger ones on the right, then sort each side.

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
    echanger(&tab[i], &tab[fin - 1]);   // the pivot reaches its place
    return i;
}
```

`O(n log n)` on average, `O(n^2)` if the pivots are systematically extreme, in
place and **not stable**. This is `tri3`.

## Counting sort

No comparison: we count the occurrences of each value (between `0` and
`max`), then rewrite the array in order.

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

`O(n + max)`: very fast if the range of values is small, wasteful otherwise. It
assumes that all the values are in `[0, max]`. This is `tri4`.

## Comparing

| Sort | Best | Average | Worst | Space | Stable | In place |
|---|---|---|---|---|---|---|
| Insertion | O(n) | O(n²) | O(n²) | O(1) | yes | yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | yes | no |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | no | yes |
| Counting | O(n + k) | O(n + k) | O(n + k) | O(k) | — | no |

`k` denotes the range of values (`max + 1`). The "worst" of quicksort happens
when the pivot is always the smallest or the largest — for example on an
already sorted array with the pivot at the end (its stack space then rises to
`O(n)`). The stability of counting sort is only visible in the cumulative-count
variant: the one in `tri4` only stores integers, where it has no observable
effect.

## `qsort` and the comparator

The library provides `qsort` (often an improved quicksort). You give it the
size of an element and a comparison.

```c
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);     // -1, 0 or +1 without an overflowing subtraction
}

qsort(tab, n, sizeof tab[0], cmp_int);
```

`(x > y) - (x < y)` returns exactly `-1`, `0` or `1`. The comparator must
define a **total** order: if it is inconsistent (for example `a - b` that
overflows), `qsort` can misbehave. This is `structs3` and `structs8` in the
`06_structs` section.

## Binary search on a sorted array

Once the array is sorted, we search in `O(log n)`:

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

It **requires** a sorted array; on an unordered array, it concludes nothing.

## The takeaway

Choose your sort according to three questions: **is the range of values small**
(counting), **must the worst case be guaranteed** (merge), **does stability
matter** (merge, insertion). And remember that a sorted array opens the door
to binary search.

Related exercises: `tri1`..`tri4`.
