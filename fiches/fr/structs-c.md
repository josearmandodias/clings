# Les structures en C — fiche

Une `struct` regroupe des champs de types différents dans un seul objet ; un
`typedef` lui donne un nom d'un seul mot. C'est un **agrégat**, sans méthode ni
constructeur, qui se copie à l'affectation. Cette fiche accompagne le chapitre
`06_structs` (à ne pas confondre avec `structures-c.md`, qui traite des listes,
piles, arbres et tables).

## Déclarer un type

```c
struct Point { int x; int y; };      // sans typedef : « struct Point »

typedef struct { int x; int y; } Point;   // avec typedef : « Point »
Point p = {3, 4};
```

Avec un `typedef` de struct **auto-référente** (liste chaînée), le nom doit être
répété à l'intérieur :

```c
typedef struct Noeud {
    int           valeur;
    struct Noeud *suivant;
} Noeud;
```

## Initialisation désignée

```c
Point a = {.x = 1, .y = 2};    // explicite, insensible à l'ordre
Point b = {0};                 // tous les champs à zéro
Point c = a;                   // copie champ à champ
c.x = 99;                      // a n'est pas modifié
```

Les champs non nommés sont mis à zéro. L'affectation copie **tout** : c'est
l'exercice `structs1`.

## Passage par valeur ou par pointeur

Par valeur, la fonction reçoit une copie et ne peut pas modifier l'original. Par
pointeur, elle reçoit l'adresse et accède aux champs avec `->`, qui est du sucre
pour `(*p).champ`.

```c
void deplacer(Point *p, int dx, int dy)   // modifie l'appelant
{
    p->x += dx;
    p->y += dy;
}

int norme_carree(const Point *p)          // ne modifie pas : const
{
    return p->x * p->x + p->y * p->y;
}

deplacer(&p, 2, 2);
```

`const Point *` évite la copie **et** documente l'intention. C'est `structs2`.

## Structures imbriquées

```c
typedef struct { Point centre; int rayon; } Cercle;

int contient(const Cercle *c, Point p)
{
    int dx = p.x - c->centre.x;
    int dy = p.y - c->centre.y;
    return dx * dx + dy * dy <= c->rayon * c->rayon;   // pas de sqrt
}
```

Comparer des carrés évite `<math.h>` et les erreurs d'arrondi. C'est `structs5`.

## Padding et alignement

Le processeur veut lire un `int` à une adresse multiple de 4. Le compilateur
insère donc du **remplissage** entre les champs, et l'ordre change la taille :

```c
typedef struct { char a; int b; char c; } Mauvais;   // 12 octets
typedef struct { int b; char a; char c; } Bon;       //  8 octets
```

Mettre les champs du plus large au plus étroit réduit le gaspillage.
`offsetof(type, champ)`, dans `<stddef.h>`, donne la position d'un champ :

```c
offsetof(Bon, b)   // 0
offsetof(Bon, a)   // 4
```

Le padding dépend de la plateforme, et `sizeof` l'inclut. C'est `structs6`.

## `union` et union étiquetée

Une `union` superpose ses membres dans le même espace : elle n'en contient qu'un
**seul** à la fois, et sa taille est celle du plus grand.

```c
typedef enum { ENTIER, REEL } Type;

typedef struct {
    Type type;                       // l'étiquette
    union { long i; double d; } valeur;
} Nombre;

double en_double(const Nombre *n)
{
    return n->type == ENTIER ? (double)n->valeur.i : n->valeur.d;
}
```

L'étiquette dit quelle variante lire : sans elle, impossible de savoir. C'est
l'**union étiquetée**, ancêtre des `enum` de Rust. C'est `structs7`.

## Pointeur de fonction dans un champ

Une struct peut ranger une fonction à côté de ses données :

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

C'est ainsi qu'on représente une « opération » ou une sorte de petit objet.
C'est `structs9`.

## `qsort` et les comparateurs

`qsort` ne connaît pas tes types : tu lui donnes la taille d'un élément et une
fonction de comparaison.

```c
int cmp(const void *a, const void *b)
{
    const Personne *pa = a;
    const Personne *pb = b;
    if (pa->age != pb->age)
        return pa->age < pb->age ? -1 : 1;     // jamais pa->age - pb->age
    return strcmp(pa->nom, pb->nom);           // départage des ex æquo
}

qsort(gens, n, sizeof gens[0], cmp);
```

Le comparateur renvoie `< 0`, `0` ou `> 0`. **Ne renvoie pas `a - b`** sur des
`int` : la soustraction peut déborder. Pour deux clés, compare la première puis
la seconde en cas d'égalité. C'est `structs3` et `structs8`.

## Parcours et recherche dans un tableau de structs

```c
int trouver(const Personne *gens, size_t n, const char *nom)
{
    for (size_t i = 0; i < n; i++) {
        if (strcmp(gens[i].nom, nom) == 0) return (int)i;
    }
    return -1;
}
```

`strcmp(...) == 0` teste l'égalité du **contenu** ; comparer deux `char *` avec
`==` ne compare que les adresses. C'est `structs10`, et `structs4` applique les
mêmes idées à une liste chaînée.

## Le réflexe

Trois questions : **par valeur ou par pointeur** (veut-on copier ou modifier ?),
**la copie est-elle superficielle ou profonde** (des pointeurs dans la struct ?),
**l'ordre des champs est-il optimal**. Réponds, et la structure reste petite et
sûre.

Exercices liés : `structs1`..`structs10`.
