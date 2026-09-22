# Recursion in C — cheat sheet

A recursive function calls itself on a **smaller** version of the
problem, until a **base case** that it solves without recursing. Each call
pushes a frame; recursion works as long as the depth stays bounded.
This cheat sheet accompanies the `09_recursion` chapter.

## The two pieces

```c
unsigned long factorielle(unsigned n)
{
    if (n <= 1) return 1;              // base case
    return n * factorielle(n - 1);     // recursive case: smaller
}
```

A correct recursive scheme checks two things:

1. the base case is reached from the starting input;
2. at each call, the argument **moves closer** to the base case.

If either is missing, it is infinite recursion, then stack overflow
(`stack overflow`). This is `recursion1`.

## The call stack

Each call creates a frame: parameters, local variables, return address.

```
factorielle(3)
  -> factorielle(2)
       -> factorielle(1)
            -> 1            (base case)
       <- 2 * 1 = 2
  <- 3 * 2 = 6
```

Memory is freed on return, in reverse order. The depth is therefore
limited (a few thousand to a few tens of thousands of frames). An iterative version
has only a loop, hence a constant depth.

## Fast exponentiation

Computing `base^exp` naively takes `exp` multiplications; by squaring,
only `log exp`.

```c
long puissance(long base, unsigned exp)
{
    if (exp == 0) return 1;                 // base case
    long demi = puissance(base, exp / 2);
    long resultat = demi * demi;
    if (exp % 2 == 1) resultat *= base;     // odd exponent
    return resultat;
}
```

`demi` is computed **once**: calling `puissance` twice would double the
work. This is `recursion2`.

## Euclid's GCD

`pgcd(a, b) = pgcd(b, a % b)`, with `pgcd(a, 0) = a`. The remainder decreases
strictly, so it terminates.

```c
int pgcd(int a, int b)
{
    a = a < 0 ? -a : a;      // absolute values to accept negatives
    b = b < 0 ? -b : b;
    if (b == 0) return a;
    return pgcd(b, a % b);
}
```

This is `recursion3`.

## Towers of Hanoi

Moving `n` disks from `de` to `vers` via `via`:

```c
void hanoi(int n, char de, char vers, char via, long *coups)
{
    if (n == 0) return;                         // nothing to do: 0 moves
    hanoi(n - 1, de, via, vers, coups);         // n-1 to the intermediate peg
    (*coups)++;                                 // move the largest
    hanoi(n - 1, via, vers, de, coups);         // bring them back
}
```

The number of moves is exactly `2^n - 1`: the recursion generates an exponential
double tree, but the algorithm is **optimal**. This is `recursion4`.

## Sum of digits

```c
int somme_chiffres(long n)
{
    if (n < 0) n = -n;
    if (n == 0) return 0;
    return (int)(n % 10) + somme_chiffres(n / 10);
}
```

`n / 10` makes one digit disappear: the problem shrinks. This is `recursion5`.

## Recursive binary search

We note the interval `[debut, fin)`, where `fin` is excluded.

```c
int recherche_binaire_rec(const int *tab, int debut, int fin, int cible)
{
    if (debut >= fin) return -1;                    // empty interval
    int milieu = debut + (fin - debut) / 2;
    if (tab[milieu] == cible) return milieu;
    if (tab[milieu] < cible)
        return recherche_binaire_rec(tab, milieu + 1, fin, cible);
    return recherche_binaire_rec(tab, debut, milieu, cible);
}
```

The half-open interval avoids special cases and bounds the depth to
`log2(n)`. The array must be sorted. This is `recursion6`.

## Recursive palindrome

A string is a palindrome if its ends are equal and if the inside is
too.

```c
int est_palindrome_rec(const char *s, int debut, int fin)
{
    if (fin - debut <= 1) return 1;                 // 0 or 1 character
    if (s[debut] != s[fin - 1]) return 0;
    return est_palindrome_rec(s, debut + 1, fin - 1);
}
```

This is `recursion7`.

## Depth and memoization

Naive recursion can redo the same work: a naive Fibonacci calls
`f(n-1)` and `f(n-2)`, which recompute `f(n-3)` twice, etc. — exponential
complexity.

```c
long fib(int n, long *memo)   // memo[i] = -1 as long as it is not computed
{
    if (n < 2) return n;
    if (memo[n] >= 0) return memo[n];
    return memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
}
```

We memoize each result once: the complexity falls back to `O(n)`, at the price
of an array and a depth of `n`. This is **memoization**, the antechamber of
dynamic programming. Often, in C, you will prefer a simple loop; recursion
shines when the problem splits naturally (trees, Hanoi,
divide-and-conquer).

## The takeaway

Every recursion has **a reachable base case** and **a decreasing argument**.
Then ask yourself what the **maximum depth** is: if it follows the size
of the input and that can be large, switch to iterative or to
memoization.

Related exercises: `recursion1`..`recursion7`.
