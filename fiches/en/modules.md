# Modules, headers and the preprocessor — cheat sheet

A C program is compiled **file by file**. Each `.c` is translated
in isolation into a *translation unit*, knowing nothing about the others; it is
the linker that then gathers everything. This cheat sheet accompanies the
`07_modules` chapter.

## Separate compilation

```sh
cc -std=c17 -Wall -Wextra -Werror -g -c math.c -o math.o
cc -std=c17 -Wall -Wextra -Werror -g -c main.c -o main.o
cc math.o main.o -o prog
```

- `-c` compiles without linking: produces an object file `.o`;
- the last command links the objects and the libraries.

Each `.c` compiles blindly. If `main.c` calls `carre`, the compiler must
know its **declaration**, otherwise the "implicit declaration" error. This is the
role of the header.

## Declaration vs definition

```c
int carre(int x);                     // declaration: a promise
int carre(int x) { return x * x; }    // definition: the code
```

A declaration states the **existence** and the type; a definition supplies the
**body** (or the storage). A function can be declared a hundred times, defined
once. The header contains the declarations. This is `modules1` and `modules2`.

## Headers and include guards

```c
/* math.h */
#ifndef MATH_H
#define MATH_H

int carre(int x);
int cube(int x);

#endif /* MATH_H */
```

Without a guard, including the same header twice would redeclare everything. The guard is that
`#ifndef` / `#define` / `#endif`; `#pragma once` is widespread but non-standard.

We include the project's headers with quotes (`#include "math.h"`, searched
first in the current directory) and the system ones with `<...>`
(`#include <stdio.h>`).

## `static` and `extern`

| Keyword | Effect |
|---|---|
| `static` on a function or a global | visible **only inside the file** ("private") |
| `static` on a local variable | keeps its value between calls, a single instance |
| `extern` on a variable | declares a variable defined elsewhere |
| `extern` on a function | reminder of an external prototype (often implicit) |

`static` on a function resolves name conflicts between two files that each
define their own `carre`. It is C's "private".

```c
static int appels;      // private counter for this file
```

## `#define` and macros

The preprocessor does **text replacement**, before any compilation.

```c
#define PI 3.14159
#define TAILLE 128

#define CARRE(x) ((x) * (x))            // parenthesize EVERYTHING
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

Without parentheses, `CARRE(1 + 2)` becomes `1 + 2 * 1 + 2`, i.e. 5. The parentheses
around **each parameter** and around the **result** are mandatory. This is
`preproc1`.

Convention: macro names in uppercase. And for anything with a type,
prefer a `static` (or `static inline`) function: no precedence surprise,
no double evaluation.

## The double evaluation trap

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
MAX(i++, j)     // i is incremented once or twice depending on the case
```

The parameter is copied text: it appears several times in the expansion.
A function, on the other hand, evaluates its arguments once. This is the reason
`preproc1` ends up asking for a real `max` function.

## `#` (stringify) and `##` (concat)

```c
#define STR(x)  #x          // argument -> string: STR(a) -> "a"
#define CONCAT(a, b) a##b   // glues two tokens: CONCAT(mon_, test) -> mon_test
```

`#` and `##` prevent their arguments from being expanded: if `VERSION` is `3`,
`STR(VERSION)` gives `"VERSION"`, not `"3"`. To expand first, go through
an intermediate macro:

```c
#define STR(x)  #x
#define XSTR(x) STR(x)      // XSTR(VERSION) -> "3"
```

This is `preproc2` and `preproc3`.

## Conditional compilation

```c
#if NIVEAU == 1
    return "debutant";
#elif NIVEAU == 2
    return "intermediaire";
#else
    return "expert";
#endif

#ifdef DEBUG
    fprintf(stderr, "valeur = %d\n", v);
#endif
```

`#if` evaluates constants **known to the preprocessor** (and `defined(X)`);
`#ifdef` tests whether a name is defined (`-DDEBUG` on the command line). The discarded
code is not even compiled. Reserve it for the platform or for diagnostics, not
for business logic. This is `preproc4`.

## The takeaway

A translation unit only sees what you declare to it: **the header says what**,
**the `.c` says how**, **the guard prevents repetition**. And for macros:
parenthesize everything, or write a function.

Related exercises: `modules1`, `modules2`, `preproc1`..`preproc4`.
