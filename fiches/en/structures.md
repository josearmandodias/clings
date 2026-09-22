# Data structures in C — cheat sheet

In C there are no containers in the language: you write your own. Two
questions come up constantly: **who owns each block** and **where is the
head**. This cheat sheet accompanies the `10_datastructures` and
`13_linked_lists` chapters.

## Reminders: allocating and owning

```c
Noeud *n = malloc(sizeof *n);   // sizeof *n, not sizeof(Noeud)
if (!n) return ...;             // malloc can fail
...
free(n);
```

A `malloc` without a `free` is a leak; a `free` on anything other than an allocated
block is undefined behaviour. ASan (and `CHECK_NO_LEAK`) is your safety net.

## Linked list

```c
typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;
```

The next node is **owned** by the previous one: freeing the list means
traversing from one to the next.

Adding at the head (O(1)):

```c
Noeud *ajouter_tete(Noeud *tete, int v)
{
    Noeud *n = malloc(sizeof *n);
    if (!n) return tete;
    n->valeur  = v;
    n->suivant = tete;
    return n;
}
```

Adding at the tail (O(n) without keeping the tail):

```c
Noeud *ajouter_queue(Noeud *tete, int v)
{
    Noeud *n = malloc(sizeof *n);
    if (!n) return tete;
    n->valeur  = v;
    n->suivant = NULL;
    if (!tete) return n;
    Noeud *c = tete;
    while (c->suivant) c = c->suivant;
    c->suivant = n;
    return tete;
}
```

Removing a value: link the previous to the next, and free the removed
node. The pointer-to-pointer avoids treating the head specially:

```c
Noeud *supprimer(Noeud *tete, int v)
{
    Noeud **lien = &tete;
    while (*lien) {
        if ((*lien)->valeur == v) {
            Noeud *mort = *lien;
            *lien = mort->suivant;
            free(mort);
            return tete;
        }
        lien = &(*lien)->suivant;
    }
    return tete;
}
```

Reversing, iterative: three pointers advancing.

```c
Noeud *inverser(Noeud *tete)
{
    Noeud *prec = NULL;
    while (tete) {
        Noeud *suiv = tete->suivant;
        tete->suivant = prec;
        prec = tete;
        tete = suiv;
    }
    return prec;
}
```

Freeing: save `suivant` **before** the `free`.

```c
void liberer(Noeud *tete)
{
    while (tete) {
        Noeud *suiv = tete->suivant;
        free(tete);
        tete = suiv;
    }
}
```

Classic mistakes:
- reading `tete->suivant` after `free(tete)`;
- losing the head (`liste = liste->suivant` without keeping the old one);
- forgetting the "insert at head" or "empty list" case;
- modifying the list while traversing it.

## Stack (LIFO)

Last in, first out. On a dynamic array:

```c
typedef struct { int *data; size_t taille, capacite; } Pile;

int pile_push(Pile *p, int v);   // grow if full, then data[taille++] = v
int pile_pop(Pile *p, int *v);   // refuse if empty, otherwise *v = data[--taille]
```

Growth by doubling: `realloc` into a **temporary**.

```c
size_t nc = p->capacite ? p->capacite * 2 : 4;
int *tmp = realloc(p->data, nc * sizeof *p->data);
if (!tmp) return 0;
p->data = tmp;
p->capacite = nc;
```

## Queue (FIFO)

First in, first out. With a **fixed** array of size `CAP`, we
wrap around with a modulo: this is the circular queue.

```c
#define CAP 4
typedef struct { int data[CAP]; size_t tete, taille; } File;

size_t queue(File *f) { return (f->tete + f->taille) % CAP; }

int file_push(File *f, int v)
{
    if (f->taille == CAP) return 0;      // full
    f->data[queue(f)] = v;
    f->taille++;
    return 1;
}

int file_pop(File *f, int *v)
{
    if (f->taille == 0) return 0;        // empty
    *v = f->data[f->tete];
    f->tete = (f->tete + 1) % CAP;
    f->taille--;
    return 1;
}
```

The modulo is the heart of the matter: `tete` and `queue` come back to the
beginning of the array instead of going past its bounds.

## Binary search tree

```c
typedef struct Arbre {
    int valeur;
    struct Arbre *gauche, *droite;
} Arbre;
```

Property: everything on the left is smaller, on the right larger.
Insertion and search are recursive.

```c
Arbre *inserer(Arbre *racine, int v)
{
    if (!racine) {
        Arbre *n = malloc(sizeof *n);
        if (!n) return NULL;
        n->valeur = v;
        n->gauche = n->droite = NULL;
        return n;
    }
    if (v < racine->valeur)      racine->gauche = inserer(racine->gauche, v);
    else if (v > racine->valeur) racine->droite = inserer(racine->droite, v);
    return racine;
}
```

**In-order** traversal (left, root, right): gives ascending order.

```c
size_t infixe(const Arbre *a, int *sortie)
{
    if (!a) return 0;
    size_t n = infixe(a->gauche, sortie);
    sortie[n++] = a->valeur;
    return n + infixe(a->droite, sortie + n);
}
```

Freeing: post-order (the children first, then the root).

```c
void liberer_arbre(Arbre *a)
{
    if (!a) return;
    liberer_arbre(a->gauche);
    liberer_arbre(a->droite);
    free(a);
}
```

## Hash table

An array of buckets; `hash(cle) % NB_BUCKETS` picks the bucket, and each
bucket is a linked list. This is "chaining".

```c
#define NB_BUCKETS 8
typedef struct Entree { char *cle; int valeur; struct Entree *suivant; } Entree;
typedef struct { Entree *buckets[NB_BUCKETS]; } Table;
```

`table_put` duplicates the key (the table does not own the caller's string),
`table_free` frees each key **then** each entry.

## Choosing

| Structure | Access | Search | Insertion | Deletion |
|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) |
| Sorted array | O(1) | O(log n) | O(n) | O(n) |
| Linked list | O(n) | O(n) | O(1) at head | O(n) |
| Stack / Queue | O(1) | O(n) | O(1) | O(1) |
| Balanced BST | O(log n) | O(log n) | O(log n) | O(log n) |
| Degenerate BST | O(n) | O(n) | O(n) | O(n) |
| Hash table | — | O(1) average | O(1) average | O(1) average |

A BST built by inserting already-sorted values degenerates into a linked
list. This is the worst case to keep in mind.

## The takeaway

For each node or entry: **who allocates it**, **who frees it**, **how do we
find the next ones when we free it**. Answer all three, and the structure
stands up.
