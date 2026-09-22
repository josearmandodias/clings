# La récursion en C — fiche

Une fonction récursive s'appelle elle-même sur une version **plus petite** du
problème, jusqu'à un **cas de base** qu'elle résout sans rappel. Chaque appel
empile une trame ; la récursion fonctionne tant que la profondeur reste bornée.
Cette fiche accompagne le chapitre `09_recursion`.

## Les deux morceaux

```c
unsigned long factorielle(unsigned n)
{
    if (n <= 1) return 1;              // cas de base
    return n * factorielle(n - 1);     // cas récursif : plus petit
}
```

Un schéma récursif correct vérifie deux choses :

1. le cas de base est atteint depuis l'entrée de départ ;
2. à chaque appel, l'argument **se rapproche** du cas de base.

Si l'un des deux manque, c'est la récursion infinie, puis le débordement de pile
(`stack overflow`). C'est `recursion1`.

## La pile d'appels

Chaque appel crée une trame : paramètres, variables locales, adresse de retour.

```
factorielle(3)
  -> factorielle(2)
       -> factorielle(1)
            -> 1            (cas de base)
       <- 2 * 1 = 2
  <- 3 * 2 = 6
```

La mémoire se libère au retour, dans l'ordre inverse. La profondeur est donc
limitée (quelques milliers à quelques dizaines de milliers de trames). Une version
itérative n'a qu'une boucle, donc une profondeur constante.

## Exponentiation rapide

Calculer `base^exp` naïvement prend `exp` multiplications ; en élevant au carré,
seulement `log exp`.

```c
long puissance(long base, unsigned exp)
{
    if (exp == 0) return 1;                 // cas de base
    long demi = puissance(base, exp / 2);
    long resultat = demi * demi;
    if (exp % 2 == 1) resultat *= base;     // exposant impair
    return resultat;
}
```

`demi` est calculé **une seule fois** : appeler `puissance` deux fois doublerait le
travail. C'est `recursion2`.

## PGCD d'Euclide

`pgcd(a, b) = pgcd(b, a % b)`, avec `pgcd(a, 0) = a`. Le reste décroît
strictement, donc ça termine.

```c
int pgcd(int a, int b)
{
    a = a < 0 ? -a : a;      // valeurs absolues pour accepter les négatifs
    b = b < 0 ? -b : b;
    if (b == 0) return a;
    return pgcd(b, a % b);
}
```

C'est `recursion3`.

## Tours de Hanoï

Déplacer `n` disques de `de` vers `vers` via `via` :

```c
void hanoi(int n, char de, char vers, char via, long *coups)
{
    if (n == 0) return;                         // rien à faire : 0 coup
    hanoi(n - 1, de, via, vers, coups);         // n-1 vers l'intermédiaire
    (*coups)++;                                 // déplacer le plus grand
    hanoi(n - 1, via, vers, de, coups);         // les ramener
}
```

Le nombre de coups vaut exactement `2^n - 1` : la récursion engendre une double
arborescence exponentielle, mais l'algorithme est **optimal**. C'est `recursion4`.

## Somme des chiffres

```c
int somme_chiffres(long n)
{
    if (n < 0) n = -n;
    if (n == 0) return 0;
    return (int)(n % 10) + somme_chiffres(n / 10);
}
```

`n / 10` fait disparaître un chiffre : le problème rétrécit. C'est `recursion5`.

## Recherche binaire récursive

On note l'intervalle `[debut, fin)`, où `fin` est exclu.

```c
int recherche_binaire_rec(const int *tab, int debut, int fin, int cible)
{
    if (debut >= fin) return -1;                    // intervalle vide
    int milieu = debut + (fin - debut) / 2;
    if (tab[milieu] == cible) return milieu;
    if (tab[milieu] < cible)
        return recherche_binaire_rec(tab, milieu + 1, fin, cible);
    return recherche_binaire_rec(tab, debut, milieu, cible);
}
```

L'intervalle semi-ouvert évite les cas particuliers et borne la profondeur à
`log2(n)`. Le tableau doit être trié. C'est `recursion6`.

## Palindrome récursif

Une chaîne est un palindrome si ses extrémités sont égales et si l'intérieur l'est
aussi.

```c
int est_palindrome_rec(const char *s, int debut, int fin)
{
    if (fin - debut <= 1) return 1;                 // 0 ou 1 caractère
    if (s[debut] != s[fin - 1]) return 0;
    return est_palindrome_rec(s, debut + 1, fin - 1);
}
```

C'est `recursion7`.

## Profondeur et mémoïsation

La récursion naïve peut refaire le même travail : un Fibonacci naïf appelle
`f(n-1)` et `f(n-2)`, qui recalculent `f(n-3)` deux fois, etc. — complexité
exponentielle.

```c
long fib(int n, long *memo)   // memo[i] = -1 tant que non calculé
{
    if (n < 2) return n;
    if (memo[n] >= 0) return memo[n];
    return memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
}
```

On mémorise chaque résultat une fois : la complexité retombe à `O(n)`, au prix
d'un tableau et d'une profondeur `n`. C'est la **mémoïsation**, antichambre de la
programmation dynamique. Souvent, en C, on préférera une simple boucle ; la
récursion brille quand le problème se découpe naturellement (arbres, Hanoï,
diviser-pour-régner).

## Le réflexe

Toute récursion a **un cas de base atteignable** et **un argument qui décroît**.
Demande-toi ensuite quelle est la **profondeur maximale** : si elle suit la taille
de l'entrée et que celle-ci peut être grande, passe à l'itératif ou à la
mémoïsation.

Exercices liés : `recursion1`..`recursion7`.
