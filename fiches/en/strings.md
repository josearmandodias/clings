# Strings in C — cheat sheet

A C string is not a language type: it is an array of `char` terminated
by a null byte `'\0'`. All the functions of `<string.h>` stop at that
byte; if it is missing, they read past the array. This cheat sheet accompanies
the `04_strings` chapter.

## `char` and the null byte

```c
char c = 'A';        // a character, with code 65
char s[] = "ABC";    // { 'A', 'B', 'C', '\0' }: 4 bytes
```

`'A'` is an `int` equal to the character code; `"A"` is a string (2 bytes).
The length in the `strlen` sense does **not** count the `'\0'`. A string of `n`
characters therefore always takes `n + 1` bytes.

## Read-only literal or modifiable array

```c
char  *p = "bonjour";   // p points to a literal, often read-only
char  t[] = "bonjour";  // t copies the 8 bytes into a modifiable array

t[0] = 'B';             // OK
p[0] = 'B';             // UB: segfault at runtime
```

However close a literal's type is to `char[]`, modifying its content is
undefined behaviour. As soon as you need to write into it, declare an **array**.
This is the `strings4` exercise.

## The essential functions

| Function | Role | Returns |
|---|---|---|
| `strlen(s)` | length excluding `'\0'` | `size_t` |
| `strcpy(dst, src)` | copies the whole string | `dst` |
| `strncpy(dst, src, n)` | copies at most `n` bytes | `dst` |
| `strcmp(a, b)` | compares | `< 0`, `0`, `> 0` |
| `strchr(s, c)` | looks for a character | pointer or `NULL` |
| `strstr(s, sub)` | looks for a substring | pointer or `NULL` |

- `strcmp` compares the bytes as `unsigned char` and stops at the
  first difference; if one is a prefix of the other, the shorter is
  smaller.
- `strchr(s, '\0')` returns a pointer to the terminator: the `'\0'` is
  part of the string. This is `strings5` and `strings10`.

## `snprintf`: writing without overflowing

`strcpy` and `strcat` do not know the size of the destination. Prefer
`snprintf`, which takes the size of the **whole** buffer (`'\0'` included) and truncates
cleanly instead of overflowing.

```c
int n = snprintf(dst, taille, "Bonjour %s", nom);
```

`snprintf` returns the number of bytes it **would have needed** to write, excluding
the terminator: so `n >= taille` signals a truncation. With `taille == 0`, nothing
is written and the return value is still computed.

```c
int saluer(char *dst, size_t taille, const char *nom)
{
    int n = snprintf(dst, taille, "Bonjour %s", nom);
    return n >= 0 && (size_t)n < taille;   // 1 if everything fit
}
```

This is the `strings2` exercise. `strcpy`/`strcat` remain correct only when
the caller has proven that the destination is large enough.

## `strlcat` and `strlcpy` (mention)

On BSD and macOS, `strlcat(dst, src, taille)` concatenates while guaranteeing a final
`'\0'` and returns the length the string would have had without truncation; with
`taille == 0`, it returns `strlen(src)` without reading `dst`. It is **not** in
the ISO C standard: for portable code, stick with `snprintf`. This is `strings6`.

## Lowercase, uppercase: watch the type

`tolower`/`toupper` expect "an `unsigned char` converted to `int`" (or
`EOF`). Passing them a negative `char` is undefined behaviour.

```c
#include <ctype.h>
c = (char)tolower((unsigned char)c);
```

The rule holds for `isalpha`, `isdigit`, `isspace`, etc. This is the delicate point
of `strings9`.

## Traversing a string

A loop stops at the `'\0'`:

```c
size_t ma_strlen(const char *s)
{
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}
```

Pointer variant, equivalent: `while (*s) { s++; n++; }`.

## Reimplementing `strcpy`

```c
char *ma_strcpy(char *dst, const char *src)
{
    char *retour = dst;
    while ((*dst++ = *src++) != '\0') { }
    return retour;
}
```

The assignment copies, and then its value serves as the condition: the `'\0'` is copied
**and** stops the loop. This is `strings3`.

## Reversing a string

We swap the ends without ever touching the `'\0'`, stopping at `n / 2`.

```c
void inverser(char *s)
{
    size_t n = strlen(s);
    for (size_t i = 0; i < n / 2; i++) {
        char tmp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = tmp;
    }
}
```

This is `strings8`.

## Palindrome

Two indices moving toward each other; we compare the `tolower` of both sides to
ignore case without breaking the accented bytes.

```c
int est_palindrome(const char *s)
{
    size_t i = 0, j = strlen(s);
    while (i < j) {
        j--;
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j]))
            return 0;
        i++;
    }
    return 1;
}
```

An empty string or a one-character string is a palindrome. This is `strings9`.

## Counting words

A word is a maximal run of characters that are not whitespace: counting
words amounts to counting the whitespace -> non-whitespace transitions.

```c
size_t compter_mots(const char *s)
{
    size_t n = 0;
    int dans_mot = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) {
            dans_mot = 0;
        } else if (!dans_mot) {
            dans_mot = 1;
            n++;
        }
    }
    return n;
}
```

This is `strings7`.

## The takeaway

Every string is an array with one more byte than its length. Before writing:
**does the buffer have room for the `'\0'`**, **is the write bounded**,
**is the source modifiable**. And for case, always cast to
`unsigned char`.

Related exercises: `strings1`..`strings10`.
