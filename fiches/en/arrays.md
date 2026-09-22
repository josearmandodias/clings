# Arrays in C — cheat sheet

A C array is a **contiguous** block of elements of the same type, with no stored
length and no bounds checking. Understanding these three facts settles most of
the exercises in the section. This cheat sheet accompanies the `03_arrays` chapter.

## Declaring and initializing

```c
int a[5];                  // 5 uninitialized int
int b[5] = {1, 2, 3, 4, 5};
int c[5] = {1, 2};         // {1, 2, 0, 0, 0}: the rest is zeroed
int d[5] = {0};            // all zero, the idiom to remember
int e[]  = {1, 2, 3};      // size deduced: 3
```

A partial initialization fills the rest with zeros. An **uninitialized local**
variable, on the other hand, contains anything: never read it before writing
it.

## `sizeof` and decay

Where the array is declared, `sizeof` gives its total size. Passed to a
function, it **decays** into a pointer to its first element: the length is
lost.

```c
int tab[5];
sizeof(tab) / sizeof(tab[0])   // 5, only here

void f(int *tab) {
    sizeof(tab);   // 8: the size of a pointer, not of the array
}
```

Hence the rule: **every function that receives an array also receives its length**.

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

The `const` promises that the elements are not modified. This is `arrays1`.

## Bounds

Valid indices go from `0` to `n - 1`. C checks nothing: writing
`tab[n]` overwrites the neighbouring memory.

```c
#define N 10
int tab[N];
for (int i = 0; i < N; i++) {   // NOT <=
    tab[i] = i * i;
}
```

ASan reports `stack-buffer-overflow` and gives the faulty address. Learning to
read that report is precisely the goal of `arrays2`.

## Two-dimensional arrays

`int m[3][4]` is a block of 12 `int`, contiguous rows: these are not lists of
pointers.

```
m[i][j]  ==  *(base + i * 4 + j)      // 4 = number of columns
```

The order is "row-major": `m[0][3]` is immediately followed by
`m[1][0]`. Passing a 2D array to a function forces you to fix the number of columns:

```c
void remplir(int m[3][4]);                    // equivalent to int (*m)[4]
void transpose(const int e[3][4], int s[4][3]);
```

This is `arrays3` and `arrays8` (matrix product: three nested loops).

## Traversal and first maximum

We keep the best candidate and update it. For the **first** maximum,
we replace only on a strict `>`, never on `>=`.

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

This is `arrays4`.

## Reversing in place

Two indices moving toward each other, a temporary, and we stop at the middle.

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

`n / 2` covers even and odd sizes. This is `arrays5`.

## Left rotation

Rotating left by `k` brings `tab[k]` to the front. First we bring `k`
back into `[0, n)`. Three reversals are enough, with no auxiliary array:

```c
void rotation_gauche(int *tab, size_t n, size_t k)
{
    if (n == 0) return;          // otherwise k %= n divides by zero
    k %= n;
    inverser(tab, k);
    inverser(tab + k, n - k);
    inverser(tab, n);
}
```

`{1, 2, 3, 4, 5}` with `k = 2` gives `{3, 4, 5, 1, 2}`. This is `arrays6`.

## Binary search

On a **sorted** array, we eliminate half the candidates at each step.
The half-open interval `[debut, fin)` avoids special cases.

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

Compute the middle with `debut + (fin - debut) / 2` rather than `(debut + fin) / 2`,
to avoid any overflow on large indices. This is `arrays7`.

## `memcpy` and `memmove`

`memcpy(dst, src, n)` copies `n` bytes; `memmove` does the same but allows
**overlap**. To remove an element by shifting the remainder, source and
destination overlap: so it is `memmove`.

```c
void supprimer(int *tab, size_t *n, size_t pos)
{
    memmove(tab + pos, tab + pos + 1, (*n - pos - 1) * sizeof *tab);
    (*n)--;
}
```

Using `memcpy` where there is overlap is undefined behaviour;
ASan talks about `memcpy-param-overlap`. This is `arrays9`.

## The takeaway

Faced with an array, three questions: **who knows its length**, **do the indices
really go from `0` to `n-1`**, **do the copied zones overlap**. Three
questions, three bugs avoided.

Related exercises: `arrays1`..`arrays9`.
