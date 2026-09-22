# Memory in C — cheat sheet

In C, two areas share the work: the **stack** (automatic, short-lived)
and the **heap** (allocated on demand, freed by hand). The central question
is not "how to allocate" but **who owns the block and when to free it**. This
cheat sheet accompanies the `05_memory` chapter.

## Stack vs heap

```c
int  local[10];                        // stack: destroyed when the function returns
int *tas = malloc(10 * sizeof *tas);   // heap: lives until free
```

| | Stack | Heap |
|---|---|---|
| Lifetime | the call frame | until `free` |
| Size | limited, fixed | large, on demand |
| Speed | very fast | slower |
| Freeing | automatic | manual |

Returning the address of a local variable gives a **dangling pointer**: the
memory is recycled as soon as the function returns. If the data must
survive, it must come from the heap. This is `memory1`.

## `malloc`, `calloc`, `realloc`, `free`

```c
#include <stdlib.h>

void *p = malloc(n * sizeof *p);        // n elements, uninitialized
void *q = calloc(n, sizeof *q);         // n elements, zeroed
void *r = realloc(p, m * sizeof *p);    // resizes (may move)
free(r);
```

- `malloc` returns `NULL` on failure: always test it;
- `calloc(n, taille)` zeroes the memory **and** checks by itself that `n * taille` does
  not overflow;
- `realloc(NULL, n)` behaves like `malloc(n)`; `realloc(p, 0)` frees the
  block (or returns `NULL` depending on the implementation).

Write `sizeof *p`, not `sizeof(int)`: the expression stays correct if the type
changes.

## The overflow guard

Before a `malloc(n * sizeof *p)`, check that the multiplication fits in a
`size_t`:

```c
#include <stdint.h>
if (n == 0 || n > SIZE_MAX / sizeof(int)) {
    return NULL;                 // once the product has overflowed, it is too late
}
int *t = calloc(n, sizeof(int));
```

`SIZE_MAX` comes from `<stdint.h>`. The guard goes **before** the multiplication.
This is `memory6`.

## Leaks, use-after-free, double free

| Fault | What happens | What the tool says |
|---|---|---|
| Forgetting `free` | memory grows without end | `CHECK_NO_LEAK` / LeakSanitizer |
| Reading after `free` | inconsistent value | `heap-use-after-free` |
| `free` twice | the allocator is corrupted | `double-free` |
| Returning a local | dead pointer | `stack-use-after-return` |

Three reflexes:

1. free as late as possible, in **one single place**;
2. set the pointer to `NULL` right after the `free`;
3. check that every `malloc` has exactly one owner.

```c
free(p);
p = NULL;          // free(NULL) does nothing: it is harmless
```

This is `memory2`, `memory3` and `memory4`.

## Ownership and deep copy

Copying a struct (`*c = *p`) copies the pointers, not what they point to: the
two then point to the **same** string. For a real clone, you must duplicate
the bytes.

```c
Personne *personne_clone(const Personne *p)
{
    Personne *c = malloc(sizeof *c);
    if (c == NULL) return NULL;
    c->age = p->age;
    c->nom = malloc(strlen(p->nom) + 1);      // don't forget the + 1
    if (c->nom == NULL) { free(c); return NULL; }
    strcpy(c->nom, p->nom);
    return c;
}
```

Free the partial copy if the second allocation fails. This is `memory10`.

## A dynamic array that grows

Doubling the capacity gives an amortized constant cost per addition
(0 -> 4 -> 8 -> 16...). With `realloc`, always go through a **temporary**:

```c
size_t nc = v->capacite ? v->capacite * 2 : 4;
int *tmp = realloc(v->data, nc * sizeof *tmp);
if (tmp == NULL) return 0;        // v->data stays intact
v->data = tmp;
v->capacite = nc;
v->data[v->taille++] = valeur;
return 1;
```

Writing `v->data = realloc(v->data, ...)` would lose the original block if `realloc`
fails. This is `memory5` and `memory8`.

## Dynamic matrix

Two levels of allocation: the array of pointers (the rows), then each
row.

```c
int **creer_matrice(size_t lignes, size_t colonnes)
{
    int **m = malloc(lignes * sizeof *m);
    if (m == NULL) return NULL;
    for (size_t i = 0; i < lignes; i++) {
        m[i] = malloc(colonnes * sizeof *m[i]);
        if (m[i] == NULL) {
            liberer_matrice(m, i);     // frees only what was allocated
            return NULL;
        }
    }
    return m;
}
```

On the error path, free what came before: no leak even when not everything
succeeds. This is `memory7`.

## Freeing a struct that owns

The order matters: first what the struct **owns**, then the struct
itself.

```c
void personne_liberer(Personne *p)
{
    if (p == NULL) return;
    free(p->nom);   // the string first
    free(p);        // then the shell
}
```

This is `memory9` and `memory11` (free on **all** exit paths, not
only the nominal path).

## The takeaway

For each block, three questions: **where does it come from**, **until when is it
valid**, **who frees it**. A `malloc` without an owner is a leak; a
`free` without an owner is a double free.

Related exercises: `memory1`..`memory11`.
