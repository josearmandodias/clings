# Les types en C — fiche

Un type dit combien d'octets occupe une valeur **et** comment interpréter ces
octets : entier signé, entier non signé, flottant. La plupart des bugs de cette
section viennent d'une conversion oubliée ou d'un format `printf` qui ne
correspond pas. Cette fiche accompagne le chapitre `01_types`.

## Entiers et tailles

```c
char      c;    // 1 octet
short     s;    // au moins 2
int       i;    // au moins 2, en pratique 4
long      l;    // au moins 4 ; 8 sur Linux/macOS 64 bits, 4 sur Windows
long long ll;   // au moins 8
```

`sizeof` donne la taille **en octets**, de type `size_t` :

```c
sizeof(char)   // 1, toujours, par définition
sizeof(int)    // 4 sur la plupart des machines
sizeof(long)   // 8 sur macOS/Linux 64 bits
```

Les bornes sont dans `<limits.h>` :

```c
#include <limits.h>
INT_MAX     //  2147483647
INT_MIN     // -2147483648
UINT_MAX    //  4294967295u
LONG_MAX
```

`<stdint.h>` fournit des tailles exactes, à préférer pour un format binaire :
`int32_t`, `uint8_t`, `int64_t`.

## Signé, non signé et conversions

Un `unsigned` ne peut pas être négatif ; sa plage est `0 .. 2^n - 1`. Le piège
classique compare un signé et un non signé : le signé est converti en non signé,
et un négatif devient énorme.

```c
int    i = -1;
size_t n = 10;
if (i < n) { ... }   // i converti en SIZE_MAX : la condition est fausse !
```

Correctif : donner à l'index le type de la taille (`size_t i`), ou comparer
explicitement. C'est l'exercice `types2`.

Les conversions entre types se font souvent sans le dire. Un cast rend
l'intention explicite :

```c
double d = (double)somme / n;   // sinon, division entière
```

## Division entière

Entre entiers, `/` tronque **vers zéro** :

```c
 7 / 2   //  3
-7 / 2   // -3   (pas -4)
```

Dès qu'un opérande est flottant, la division est flottante :

```c
7 / 2           // 3
7 / 2.0         // 3.5
(double)7 / 2   // 3.5
```

Le piège de `types3` : dans une fonction qui renvoie `double`, `return somme / n;`
calcule d'abord la division **entière**, puis convertit. Il faut convertir un
opérande **avant** l'opération.

## Modulo et négatifs

`%` suit le signe du **dividende** :

```c
 7 % 3   //  1
-7 % 3   // -1
```

Pour un reste toujours dans `[0, n)`, avec `n > 0` :

```c
int modulo_positif(int a, int n)
{
    int r = a % n;
    return r < 0 ? r + n : r;
}
```

Attention : `INT_MIN / -1` et `INT_MIN % -1` sont des comportements indéfinis,
car le résultat quotient n'est pas représentable. C'est `types5`.

## Débordement signé

Dépasser `INT_MAX` sur un `int` est un **comportement indéfini** (UB) :

```c
int x = INT_MAX;
x + 1;                // UB : le compilateur peut supposer que ça n'arrive jamais
(long)INT_MAX + 1     // OK : l'addition est faite en long
```

Change le **type de l'opération**, pas seulement celui du résultat : `return a + b;`
avec deux `int` calcule en `int`, puis convertit. Écris `return (long)a + b;`.
UBSan signale `signed integer overflow`.

Le débordement **non signé**, lui, est défini : il reboucle modulo `2^n`. C'est
`types4`.

## Flottants

```c
float       f  = 0.5f;   // ~7 chiffres significatifs
double      d  = 0.5;    // ~15 chiffres, le choix par défaut
long double ld = 0.5L;
```

Ils ne représentent pas exactement les décimaux : `0.1 + 0.2` n'est pas
exactement `0.3`. On ne compare donc pas avec `==` :

```c
#include <math.h>
int presque_egaux(double a, double b)
{
    return fabs(a - b) < 1e-9;
}
```

L'epsilon doit être choisi selon l'échelle des nombres (comparaison absolue ou
relative). Convertir un flottant en entier **tronque vers zéro** :
`(int)2.7 == 2`, `(int)-2.4 == -2`. Pour arrondir : `round`, `floor`, `ceil` de
`<math.h>`. C'est `types6` et `types7`.

## Formater avec `printf`

| Spécificateur | Type attendu |
|---|---|
| `%d` | `int` |
| `%u` | `unsigned int` |
| `%ld`, `%lu` | `long`, `unsigned long` |
| `%zu` | `size_t` |
| `%f` | `double` (et `float`, promu) |
| `%Lf` | `long double` |
| `%c` | `int` (un caractère) |
| `%s` | `char *` |
| `%p` | `void *` |
| `%x`, `%X` | entier en hexadécimal |

Un mauvais spécificateur est un comportement indéfini silencieux. Quand le
format est une chaîne littérale, le compilateur le vérifie sous `-Wall` et
refuse par exemple `printf("%d", 0.5)`. C'est `types1`.

## `enum`

Un `enum` nomme des constantes entières :

```c
typedef enum { PRINTEMPS, ETE, AUTOMNE, HIVER } Saison;

PRINTEMPS   // 0
ETE         // 1
```

Associé à un `switch`, il rend le traitement exhaustif visible ; sous `-Wswitch`,
le compilateur signale un cas oublié. C'est `types8`.

## Le réflexe

Avant chaque opération, trois questions : **quel est le type des deux
opérandes**, **quel est le type du résultat**, **le format `printf` correspond-il
au type exact**. Avec ces réponses, la plupart des pièges de la section tombent.

Exercices liés : `types1`..`types8`.
