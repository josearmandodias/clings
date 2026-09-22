# Les pointeurs en C — fiche

## Les deux opérateurs

```c
int  x = 10;
int *p = &x;   // &x : l'adresse de x
*p = 42;       // *p : la case pointée -> écrit dans x
```

`&` fabrique une adresse, `*` la suit. Ils s'annulent : `*&x` vaut `x`.

Piège de lecture : dans `int *p = &x;` l'étoile fait partie de la
**déclaration** (« p est un pointeur sur int »). Partout ailleurs, `*p` est un
**déréférencement**. Même symbole, deux rôles.

## Lire une déclaration

De l'intérieur vers l'extérieur, en partant du nom :

```c
int *p;            // p pointe sur un int
int **pp;          // pp pointe sur un pointeur sur int
int *a[4];         // a : tableau de 4 pointeurs sur int
int (*b)[4];       // b : pointeur sur un tableau de 4 int
int (*f)(int);     // f : pointeur sur une fonction int -> int
```

Les parenthèses changent tout : `int *a[4]` lie l'étoile à `a[4]` (4 pointeurs),
`int (*b)[4]` lie l'étoile à `b` (un seul pointeur, vers un tableau).

```c
sizeof(a) == 4 * sizeof(int *);   // le tableau de pointeurs
sizeof(*b) == 4 * sizeof(int);    // un tableau entier
```

## const et pointeurs

```c
const char *s;            // s bouge, les char pointés sont en lecture seule
char * const s = buf;     // s figé, les char pointés sont modifiables
const char * const s;     // les deux sont figés
const char *const *mots;  // tableau de pointeurs constants vers du const char
```

Le `const` porte sur ce qui est à sa gauche ; s'il n'y a rien à sa gauche, sur
ce qui est à sa droite. En pratique tu écriras `const char *` dans 95 % des
cas : c'est la promesse « je lis, je ne touche pas ». Une fonction qui n'écrit
pas dans une chaîne doit la prendre en `const char *`.

## Modifier une variable de l'appelant

Tout passe par copie en C. Pour qu'une fonction modifie ta variable, elle doit
recevoir son adresse.

```c
void incr(int *n) { (*n)++; }   // parenthèses obligatoires
int v = 1;
incr(&v);                        // v vaut 2
```

`(*n)++` incrémente la valeur ; `*n++` incrémenterait le pointeur. Les
parenthèses ne sont pas décoratives.

## NULL

`NULL` est l'adresse « nulle part ». Déréférencer un pointeur nul plante.

```c
if (p != NULL) { ... }   // ou simplement if (p)
```

Trois moments où le tester : après un `malloc`, après une fonction qui peut
échouer, et sur un paramètre de sortie optionnel.

Un pointeur **non initialisé** n'est pas `NULL` : il contient une adresse
quelconque. C'est le « wild pointer », et c'est pire que `NULL` parce qu'il
peut passer des tests sans qu'on s'en aperçoive. Initialise toujours :

```c
int *p = NULL;
```

## Le patron « paramètre de sortie »

Le C n'a ni tuple, ni `Option`, ni `Result`. Une fonction renvoie un statut et
écrit son résultat dans un pointeur fourni par l'appelant.

```c
int parse_positif(const char *s, int *out)
{
    int v = atoi(s);
    if (v <= 0)   return 0;      // échec : *out n'est pas touché
    if (out)      *out = v;      // out peut légitimement être NULL
    return 1;
}
```

## Tableaux et arithmétique

Un tableau passé à une fonction se dégrade en pointeur sur son premier
élément. La longueur est perdue, d'où le paramètre `size_t n` systématique.

```c
tab[i]  ==  *(tab + i)     // strictement équivalent
p + 1                      // avance de sizeof(*p) octets, pas de 1
```

`sizeof(tab)` donne la taille du tableau là où il est déclaré, mais la taille
d'un pointeur (8 octets) dans la fonction qui le reçoit.

Ce qui est permis :

```c
int  tab[5];
int *fin = tab + 5;        // "one past the end" : former l'adresse est permis
ptrdiff_t n = fin - tab;   // 5 : différence de deux pointeurs du même tableau

for (int *p = tab; p != fin; p++) {
    *p = 0;                // parcours idiomatique
}
```

Ce qui ne l'est pas :

- déréférencer `fin` (un cran après le dernier élément) ;
- faire `p - q` si `p` et `q` ne pointent pas dans le même tableau ;
- comparer `p < q` dans ce cas ;
- sortir de l'autre côté (`tab - 1`), même sans déréférencer.

## Pointeurs de fonction

Une fonction a une adresse, et cette adresse a un type : c'est sa signature.

```c
int carre(int x) { return x * x; }

int appliquer(int (*f)(int), int x)   // f : pointeur de fonction
{
    return f(x);
}

appliquer(carre, 5);                  // 25
```

Un `typedef` rend la chose lisible, surtout dans une structure :

```c
typedef int (*Operation)(int, int);
int addition(int a, int b)       { return a + b; }
int multiplication(int a, int b) { return a * b; }

Operation op = addition;      // on affecte la fonction, pas &addition
op(2, 3);                     // 5
```

C'est exactement ce que `qsort` attend :

```c
static int cmp(const void *a, const void *b)
{
    const int *pa = a;
    const int *pb = b;
    if (*pa < *pb) return -1;
    return *pa > *pb;
}

qsort(tab, n, sizeof(tab[0]), cmp);
```

## void *, memcpy et le générique

`void *` est un pointeur « vers on ne sait pas quoi ». En C (contrairement au
C++), la conversion `T *` <-> `void *` est **implicite** : pas besoin de cast.

```c
void echanger(void *a, void *b, size_t n)
{
    unsigned char *pa = a;
    unsigned char *pb = b;
    while (n--) {
        unsigned char tmp = *pa;
        *pa++ = *pb;
        *pb++ = tmp;
    }
}
```

`memcpy` et `memmove` ne connaissent que des octets, d'où leur signature en
`void *` et le paramètre de taille. `memcpy` **interdit** le recouvrement,
`memmove` l'autorise. Se tromper, c'est `memcpy-param-overlap` sous ASan.

## Qui possède la mémoire

C'est la question centrale, celle que Rust résout à ta place.

```c
int  local[10];                          // pile : meurt à la fin de la fonction
int *tas = malloc(10 * sizeof(*tas));    // tas : vit jusqu'au free
```

- ne jamais renvoyer l'adresse d'une variable locale ;
- un seul propriétaire par bloc, donc un seul `free` ;
- mettre le pointeur à `NULL` juste après le `free` ;
- `sizeof(*p)` plutôt que `sizeof(int)` : ça reste juste si le type change.

## Les fautes classiques

| Faute | Symptôme | Ce que dit ASan |
|---|---|---|
| Renvoyer une locale | valeurs aberrantes | `stack-use-after-return` |
| Lire après `free` | marche parfois, c'est pire | `heap-use-after-free` |
| `free` deux fois | corruption de l'allocateur | `double-free` |
| Oublier `free` | mémoire qui gonfle | fuite signalée en fin de programme |
| Pointeur non initialisé | plantage aléatoire | adresse invalide au hasard |
| Déréférencer `NULL` | plantage immédiat | `SEGV on unknown address 0x00` |
| Dépasser un tableau | corruption silencieuse | `stack-buffer-overflow` |

Les trois premières sont des comportements indéfinis : le programme peut très
bien « marcher » pendant des mois avant de tomber.

## Le réflexe

Devant tout pointeur, trois questions : **d'où vient cette adresse**,
**jusqu'à quand est-elle valide**, **qui est chargé de la libérer**. Si tu ne
sais pas répondre aux trois, tu as un bug en attente.

## Compiler

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```
