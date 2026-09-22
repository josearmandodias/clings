# Pointers in C — cheat sheet

## The two operators

```c
int  x = 10;
int *p = &x;   // &x: the address of x
*p = 42;       // *p: the pointed-to slot -> writes into x
```

`&` makes an address, `*` follows it. They cancel out: `*&x` equals `x`.

Reading trap: in `int *p = &x;` the star is part of the
**declaration** ("p is a pointer to int"). Everywhere else, `*p` is a
**dereference**. Same symbol, two roles.

## Reading a declaration

From the inside out, starting from the name:

```c
int *p;            // p points to an int
int **pp;          // pp points to a pointer to int
int *a[4];         // a: array of 4 pointers to int
int (*b)[4];       // b: pointer to an array of 4 int
int (*f)(int);     // f: pointer to a function int -> int
```

The parentheses change everything: `int *a[4]` binds the star to `a[4]` (4 pointers),
`int (*b)[4]` binds the star to `b` (a single pointer, to an array).

```c
sizeof(a) == 4 * sizeof(int *);   // the array of pointers
sizeof(*b) == 4 * sizeof(int);    // a whole array
```

## const and pointers

```c
const char *s;            // s moves, the pointed-to char are read-only
char * const s = buf;     // s frozen, the pointed-to char are modifiable
const char * const s;     // both are frozen
const char *const *mots;  // array of constant pointers to const char
```

The `const` applies to what is on its left; if there is nothing on its left, to
what is on its right. In practice you will write `const char *` in 95% of
cases: it is the promise "I read, I don't touch". A function that does not write
into a string must take it as `const char *`.

## Modifying a caller's variable

Everything passes by copy in C. For a function to modify your variable, it must
receive its address.

```c
void incr(int *n) { (*n)++; }   // parentheses required
int v = 1;
incr(&v);                        // v is 2
```

`(*n)++` increments the value; `*n++` would increment the pointer. The
parentheses are not decorative.

## NULL

`NULL` is the address "nowhere". Dereferencing a null pointer crashes.

```c
if (p != NULL) { ... }   // or simply if (p)
```

Three moments to test it: after a `malloc`, after a function that can
fail, and on an optional output parameter.

An **uninitialized** pointer is not `NULL`: it holds some arbitrary
address. This is the "wild pointer", and it is worse than `NULL` because it
can pass tests without you noticing. Always initialize:

```c
int *p = NULL;
```

## The "output parameter" pattern

C has no tuple, no `Option`, no `Result`. A function returns a status and
writes its result into a pointer supplied by the caller.

```c
int parse_positif(const char *s, int *out)
{
    int v = atoi(s);
    if (v <= 0)   return 0;      // failure: *out is not touched
    if (out)      *out = v;      // out may legitimately be NULL
    return 1;
}
```

## Arrays and arithmetic

An array passed to a function decays into a pointer to its first
element. The length is lost, hence the systematic `size_t n` parameter.

```c
tab[i]  ==  *(tab + i)     // strictly equivalent
p + 1                      // advances by sizeof(*p) bytes, not by 1
```

`sizeof(tab)` gives the array size where it is declared, but the size of
a pointer (8 bytes) in the function that receives it.

What is allowed:

```c
int  tab[5];
int *fin = tab + 5;        // "one past the end": forming the address is allowed
ptrdiff_t n = fin - tab;   // 5: difference of two pointers into the same array

for (int *p = tab; p != fin; p++) {
    *p = 0;                // idiomatic traversal
}
```

What is not:

- dereferencing `fin` (one past the last element);
- doing `p - q` if `p` and `q` do not point into the same array;
- comparing `p < q` in that case;
- going out the other side (`tab - 1`), even without dereferencing.

## Function pointers

A function has an address, and that address has a type: its signature.

```c
int carre(int x) { return x * x; }

int appliquer(int (*f)(int), int x)   // f: function pointer
{
    return f(x);
}

appliquer(carre, 5);                  // 25
```

A `typedef` makes it readable, especially inside a struct:

```c
typedef int (*Operation)(int, int);
int addition(int a, int b)       { return a + b; }
int multiplication(int a, int b) { return a * b; }

Operation op = addition;      // we assign the function, not &addition
op(2, 3);                     // 5
```

This is exactly what `qsort` expects:

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

## void *, memcpy and genericity

`void *` is a pointer "to who knows what". In C (unlike C++), the conversion
`T *` <-> `void *` is **implicit**: no cast needed.

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

`memcpy` and `memmove` only know about bytes, hence their `void *` signature
and the size parameter. `memcpy` **forbids** overlap, `memmove` allows it.
Getting this wrong is `memcpy-param-overlap` under ASan.

## Who owns the memory

This is the central question, the one Rust solves for you.

```c
int  local[10];                          // stack: dies at the end of the function
int *tas = malloc(10 * sizeof(*tas));    // heap: lives until free
```

- never return the address of a local variable;
- a single owner per block, hence a single `free`;
- set the pointer to `NULL` right after the `free`;
- `sizeof(*p)` rather than `sizeof(int)`: it stays correct if the type changes.

## Classic faults

| Fault | Symptom | What ASan says |
|---|---|---|
| Returning a local | garbage values | `stack-use-after-return` |
| Reading after `free` | sometimes works, which is worse | `heap-use-after-free` |
| `free` twice | allocator corruption | `double-free` |
| Forgetting `free` | memory that keeps growing | leak reported at the end of the program |
| Uninitialized pointer | random crash | random invalid address |
| Dereferencing `NULL` | immediate crash | `SEGV on unknown address 0x00` |
| Overrunning an array | silent corruption | `stack-buffer-overflow` |

The first three are undefined behaviours: the program can very well
"work" for months before falling over.

## The takeaway

Faced with any pointer, three questions: **where does this address come from**,
**until when is it valid**, **who is responsible for freeing it**. If you cannot
answer all three, you have a bug waiting to happen.

## Compiling

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```
