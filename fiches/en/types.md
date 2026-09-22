# Types in C — cheat sheet

A type says how many bytes a value occupies **and** how to interpret those
bytes: signed integer, unsigned integer, floating point. Most bugs in this
section come from a forgotten conversion or from a `printf` format that does not
match. This cheat sheet accompanies the `01_types` chapter.

## Integers and sizes

```c
char      c;    // 1 byte
short     s;    // at least 2
int       i;    // at least 2, in practice 4
long      l;    // at least 4; 8 on 64-bit Linux/macOS, 4 on Windows
long long ll;   // at least 8
```

`sizeof` gives the size **in bytes**, of type `size_t`:

```c
sizeof(char)   // 1, always, by definition
sizeof(int)    // 4 on most machines
sizeof(long)   // 8 on 64-bit macOS/Linux
```

The bounds are in `<limits.h>`:

```c
#include <limits.h>
INT_MAX     //  2147483647
INT_MIN     // -2147483648
UINT_MAX    //  4294967295u
LONG_MAX
```

`<stdint.h>` provides exact sizes, to be preferred for a binary format:
`int32_t`, `uint8_t`, `int64_t`.

## Signed, unsigned and conversions

An `unsigned` cannot be negative; its range is `0 .. 2^n - 1`. The classic
trap compares a signed and an unsigned value: the signed one is converted to
unsigned, and a negative becomes huge.

```c
int    i = -1;
size_t n = 10;
if (i < n) { ... }   // i converted to SIZE_MAX: the condition is false!
```

Fix: give the index the type of the size (`size_t i`), or compare
explicitly. This is the `types2` exercise.

Conversions between types often happen without saying so. A cast makes
the intent explicit:

```c
double d = (double)somme / n;   // otherwise, integer division
```

## Integer division

Between integers, `/` truncates **toward zero**:

```c
 7 / 2   //  3
-7 / 2   // -3   (not -4)
```

As soon as one operand is floating point, the division is floating point:

```c
7 / 2           // 3
7 / 2.0         // 3.5
(double)7 / 2   // 3.5
```

The trap of `types3`: in a function that returns `double`, `return somme / n;`
first computes the **integer** division, then converts. You must convert an
operand **before** the operation.

## Modulo and negatives

`%` follows the sign of the **dividend**:

```c
 7 % 3   //  1
-7 % 3   // -1
```

For a remainder always in `[0, n)`, with `n > 0`:

```c
int modulo_positif(int a, int n)
{
    int r = a % n;
    return r < 0 ? r + n : r;
}
```

Careful: `INT_MIN / -1` and `INT_MIN % -1` are undefined behaviour,
because the quotient result is not representable. This is `types5`.

## Signed overflow

Exceeding `INT_MAX` on an `int` is **undefined behaviour** (UB):

```c
int x = INT_MAX;
x + 1;                // UB: the compiler may assume it never happens
(long)INT_MAX + 1     // OK: the addition is done in long
```

Change the **type of the operation**, not only that of the result: `return a + b;`
with two `int` computes in `int`, then converts. Write `return (long)a + b;`.
UBSan reports `signed integer overflow`.

**Unsigned** overflow, on the other hand, is defined: it wraps around modulo `2^n`. This is
`types4`.

## Floating point

```c
float       f  = 0.5f;   // ~7 significant digits
double      d  = 0.5;    // ~15 digits, the default choice
long double ld = 0.5L;
```

They do not represent decimals exactly: `0.1 + 0.2` is not
exactly `0.3`. So we do not compare with `==`:

```c
#include <math.h>
int presque_egaux(double a, double b)
{
    return fabs(a - b) < 1e-9;
}
```

The epsilon must be chosen according to the scale of the numbers (absolute or
relative comparison). Converting a floating-point value to an integer **truncates toward zero**:
`(int)2.7 == 2`, `(int)-2.4 == -2`. To round: `round`, `floor`, `ceil` from
`<math.h>`. This is `types6` and `types7`.

## Formatting with `printf`

| Specifier | Expected type |
|---|---|
| `%d` | `int` |
| `%u` | `unsigned int` |
| `%ld`, `%lu` | `long`, `unsigned long` |
| `%zu` | `size_t` |
| `%f` | `double` (and `float`, promoted) |
| `%Lf` | `long double` |
| `%c` | `int` (a character) |
| `%s` | `char *` |
| `%p` | `void *` |
| `%x`, `%X` | integer in hexadecimal |

A wrong specifier is silent undefined behaviour. When the
format is a string literal, the compiler checks it under `-Wall` and
refuses, for example, `printf("%d", 0.5)`. This is `types1`.

## `enum`

An `enum` names integer constants:

```c
typedef enum { PRINTEMPS, ETE, AUTOMNE, HIVER } Saison;

PRINTEMPS   // 0
ETE         // 1
```

Combined with a `switch`, it makes exhaustive handling visible; under `-Wswitch`,
the compiler reports a forgotten case. This is `types8`.

## The takeaway

Before every operation, three questions: **what is the type of the two
operands**, **what is the type of the result**, **does the `printf` format match
the exact type**. With those answers, most of the traps in the section fall away.

Related exercises: `types1`..`types8`.
