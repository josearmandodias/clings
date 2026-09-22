# Les structures de données en C — fiche

En C, il n'y a pas de containers dans le langage : tu écris le tien. Deux
questions reviennent sans cesse : **qui possède chaque bloc** et **où est la
tête**. Cette fiche accompagne les chapitres `10_datastructures` et
`13_linked_lists`.

## Rappels : allouer et posséder

```c
Noeud *n = malloc(sizeof *n);   // sizeof *n, pas sizeof(Noeud)
if (!n) return ...;             // malloc peut échouer
...
free(n);
```

Un `malloc` sans `free` est une fuite ; un `free` sur autre chose qu'un bloc
alloué est un comportement indéfini. ASan (et `CHECK_NO_LEAK`) est ton filet.

## Liste chaînée

```c
typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;
```

Le nœud suivant est **possédé** par le précédent : libérer la liste, c'est
parcourir de proche en proche.

Ajouter en tête (O(1)) :

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

Ajouter en queue (O(n) sans garder la queue) :

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

Supprimer une valeur : relier le précédent au suivant, et libérer le nœud
retiré. Le pointeur de pointeur évite de traiter la tête à part :

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

Inverser, itératif : trois pointeurs qui avancent.

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

Libérer : sauver `suivant` **avant** le `free`.

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

Erreurs classiques :
- lire `tete->suivant` après `free(tete)` ;
- perdre la tête (`liste = liste->suivant` sans garder l'ancienne) ;
- oublier le cas « insertion en tête » ou « liste vide » ;
- modifier la liste pendant qu'on la parcourt.

## Pile (LIFO)

Dernier entré, premier sorti. Sur un tableau dynamique :

```c
typedef struct { int *data; size_t taille, capacite; } Pile;

int pile_push(Pile *p, int v);   // agrandir si plein, puis data[taille++] = v
int pile_pop(Pile *p, int *v);   // refuser si vide, sinon *v = data[--taille]
```

Croissance par doublement : `realloc` dans un **temporaire**.

```c
size_t nc = p->capacite ? p->capacite * 2 : 4;
int *tmp = realloc(p->data, nc * sizeof *p->data);
if (!tmp) return 0;
p->data = tmp;
p->capacite = nc;
```

## File (FIFO)

Premier entré, premier sorti. Avec un tableau **fixe** de taille `CAP`, on
boucle avec un modulo : c'est la file circulaire.

```c
#define CAP 4
typedef struct { int data[CAP]; size_t tete, taille; } File;

size_t queue(File *f) { return (f->tete + f->taille) % CAP; }

int file_push(File *f, int v)
{
    if (f->taille == CAP) return 0;      // pleine
    f->data[queue(f)] = v;
    f->taille++;
    return 1;
}

int file_pop(File *f, int *v)
{
    if (f->taille == 0) return 0;        // vide
    *v = f->data[f->tete];
    f->tete = (f->tete + 1) % CAP;
    f->taille--;
    return 1;
}
```

Le modulo est le cœur du sujet : `tete` et `queue` reviennent au début du
tableau au lieu de sortir de ses bornes.

## Arbre binaire de recherche

```c
typedef struct Arbre {
    int valeur;
    struct Arbre *gauche, *droite;
} Arbre;
```

Propriété : tout ce qui est à gauche est plus petit, à droite plus grand.
L'insertion et la recherche sont récursives.

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

Parcours **infixe** (gauche, racine, droite) : donne l'ordre croissant.

```c
size_t infixe(const Arbre *a, int *sortie)
{
    if (!a) return 0;
    size_t n = infixe(a->gauche, sortie);
    sortie[n++] = a->valeur;
    return n + infixe(a->droite, sortie + n);
}
```

Libérer : postordre (les enfants d'abord, puis la racine).

```c
void liberer_arbre(Arbre *a)
{
    if (!a) return;
    liberer_arbre(a->gauche);
    liberer_arbre(a->droite);
    free(a);
}
```

## Table de hachage

Un tableau de seaux ; `hash(cle) % NB_BUCKETS` choisit le seau, et chaque
seau est une liste chaînée. C'est le « chaînage ».

```c
#define NB_BUCKETS 8
typedef struct Entree { char *cle; int valeur; struct Entree *suivant; } Entree;
typedef struct { Entree *buckets[NB_BUCKETS]; } Table;
```

`table_put` duplique la clé (la table ne possède pas la chaîne de l'appelant),
`table_free` libère chaque clé **puis** chaque entrée.

## Choisir

| Structure | Accès | Recherche | Insertion | Suppression |
|---|---|---|---|---|
| Tableau | O(1) | O(n) | O(n) | O(n) |
| Tableau trié | O(1) | O(log n) | O(n) | O(n) |
| Liste chaînée | O(n) | O(n) | O(1) en tête | O(n) |
| Pile / File | O(1) | O(n) | O(1) | O(1) |
| ABR équilibré | O(log n) | O(log n) | O(log n) | O(log n) |
| ABR dégénéré | O(n) | O(n) | O(n) | O(n) |
| Table de hachage | — | O(1) moyen | O(1) moyen | O(1) moyen |

Un ABR construit en insérant des valeurs déjà triées dégénère en liste
chaînée. C'est le pire cas à garder en tête.

## Le réflexe

Pour chaque nœud ou entrée : **qui l'alloue**, **qui le libère**, **comment on
retrouve les suivants quand on le libère**. Réponds aux trois, et la structure
tient debout.
