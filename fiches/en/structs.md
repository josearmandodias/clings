# Structs in C — cheat sheet

A `struct` groups fields of different types into a single object; a
`typedef` gives it a one-word name. It is an **aggregate**, with no method and no
constructor, that is copied on assignment. This cheat sheet accompanies the
`06_structs` chapter (not to be confused with `structures.md`, which covers
lists, stacks, trees and hash tables).

## Declaring a type

```c
struct Point { int x; int y; };      // without typedef: "struct Point"

typedef struct { int x; int y; } Point;   // with typedef: "Point"
Point p = {3, 4};
```

With a **self-referential** struct `typedef` (linked list), the name must be
repeated inside:

```c
typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;
```

## Designated initialization

```c
Point a = {.x = 1, .y = 2};    // explicit, order-independent
Point b = {0};                 // all fields to zero
Point c = a;                   // field-by-field copy
c.x = 99;                      // a is not modified
```

Unnamed fields are set to zero. Assignment copies **everything**: this is
the `structs1` exercise.

## Pass by value or by pointer

By value, the function receives a copy and cannot modify the original. By
pointer, it receives the address and accesses the fields with `->`, which is
sugar for `(*p).field`.

```c
void deplacer(Point *p, int dx, int dy)   // modifies the caller
{
    p->x += dx;
    p->y += dy;
}

int norme_carree(const Point *p)          // does not modify: const
{
    return p->x * p->x + p->y * p->y;
}

deplacer(&p, 2, 2);
```

`const Point *` avoids the copy **and** documents the intent. This is `structs2`.

## Nested structs

```c
typedef struct { Point centre; int rayon; } Cercle;

int contient(const Cercle *c, Point p)
{
    int dx = p.x - c->centre.x;
    int dy = p.y - c->centre.y;
    return dx * dx + dy * dy <= c->rayon * c->rayon;   // no sqrt
}
```

Comparing squares avoids `<math.h>` and rounding errors. This is `structs5`.

## Padding and alignment

The processor wants to read an `int` at an address that is a multiple of 4. The compiler
therefore inserts **padding** between the fields, and the order changes the size:

```c
typedef struct { char a; int b; char c; } Mauvais;   // 12 bytes
typedef struct { int b; char a; char c; } Bon;       //  8 bytes
```

Putting the fields from widest to narrowest reduces the waste.
`offsetof(type, field)`, in `<stddef.h>`, gives the position of a field:

```c
offsetof(Bon, b)   // 0
offsetof(Bon, a)   // 4
```

Padding depends on the platform, and `sizeof` includes it. This is `structs6`.

## `union` and tagged union

A `union` overlays its members in the same space: it holds only **one** of them
at a time, and its size is that of the largest.

```c
typedef enum { ENTIER, REEL } Type;

typedef struct {
    Type type;                       // the tag
    union { long i; double d; } valeur;
} Nombre;

double en_double(const Nombre *n)
{
    return n->type == ENTIER ? (double)n->valeur.i : n->valeur.d;
}
```

The tag says which variant to read: without it, there is no way to know. This is
the **tagged union**, ancestor of Rust's `enum`s. This is `structs7`.

## Function pointer in a field

A struct can store a function alongside its data:

```c
typedef struct {
    char op;
    int (*calcul)(int, int);
} Operation;

int evaluer(const Operation *o, int a, int b)
{
    return o->calcul(a, b);
}
```

This is how you represent an "operation" or a kind of small object.
This is `structs9`.

## `qsort` and comparators

`qsort` does not know your types: you give it the size of an element and a
comparison function.

```c
int cmp(const void *a, const void *b)
{
    const Personne *pa = a;
    const Personne *pb = b;
    if (pa->age != pb->age)
        return pa->age < pb->age ? -1 : 1;     // never pa->age - pb->age
    return strcmp(pa->nom, pb->nom);           // tie-breaker
}

qsort(gens, n, sizeof gens[0], cmp);
```

The comparator returns `< 0`, `0` or `> 0`. **Do not return `a - b`** on
`int`: the subtraction can overflow. For two keys, compare the first then
the second in case of equality. This is `structs3` and `structs8`.

## Traversal and search in an array of structs

```c
int trouver(const Personne *gens, size_t n, const char *nom)
{
    for (size_t i = 0; i < n; i++) {
        if (strcmp(gens[i].nom, nom) == 0) return (int)i;
    }
    return -1;
}
```

`strcmp(...) == 0` tests equality of **content**; comparing two `char *` with
`==` only compares addresses. This is `structs10`, and `structs4` applies the
same ideas to a linked list.

## The takeaway

Three questions: **by value or by pointer** (do we want to copy or modify?),
**is the copy shallow or deep** (pointers inside the struct?),
**is the field order optimal**. Answer them, and the struct stays small and
safe.

Related exercises: `structs1`..`structs10`.
