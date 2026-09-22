# Files in C — cheat sheet

In C, a file is a stream of bytes represented by a `FILE *`. You open it, you
read or write, you close it. No exceptions: an error is signalled by a
**return value** and, for the OS, by `errno`. This cheat sheet accompanies the
`08_io` chapter.

## Opening and closing

```c
#include <stdio.h>

FILE *f = fopen("data.txt", "r");
if (f == NULL) {
    perror("fopen");       // prints the system message
    return 1;
}
/* ... */
fclose(f);                 // always close, especially on error
```

| Mode | Read | Write | Truncates | Initial position |
|---|---|---|---|---|
| `"r"` | yes | — | — | beginning |
| `"w"` | — | yes | yes | beginning |
| `"a"` | — | yes | — | end (append) |
| `"r+"` | yes | yes | — | beginning |
| `"w+"` | yes | yes | yes | beginning |
| `"a+"` | yes | yes | — | end |

Add a `b` for binary (`"rb"`, `"wb"`), especially useful under Windows.
`fopen` returns `NULL` if the file does not exist (in `"r"`) or is not
accessible.

## Reading text with `fgets`

`fgets(buf, taille, f)` reads at most `taille - 1` characters, keeps the `'\n'` if it
fits, adds `'\0'` and returns `NULL` at end of file or on error. It **cannot**
overflow, unlike `gets` (removed from the language in 2011).

```c
int compter_lignes(const char *chemin)
{
    FILE *f = fopen(chemin, "r");
    if (f == NULL) return -1;
    char ligne[256];
    int n = 0;
    while (fgets(ligne, sizeof ligne, f) != NULL) {
        n++;
    }
    fclose(f);
    return n;
}
```

An empty file counts 0 lines; a last line without a `'\n'` counts as 1.
This is `io1`.

## Writing text

```c
fprintf(f, "%d\n", valeur);   // like printf, to a FILE *
fputs("texte", f);            // without adding '\n'
fputc('x', f);
fflush(f);                    // forces the write to disk
```

`fprintf` returns a negative number on error: check it on critical writes.
`fputs` does not add a newline. This is `io2`.

## Reading and writing binary

```c
size_t n = fwrite(tab, sizeof *tab, nb, f);   // memory -> file
size_t m = fread(buf, sizeof *buf, nb, f);    // file -> memory
```

Both return the **number of elements** processed: compare it to `nb` to
detect a failure or an end of file. `fwrite`/`fread` do no
conversion, it is the raw memory.

```c
int sauver_point(const char *chemin, const Point *p)
{
    FILE *f = fopen(chemin, "wb");
    if (f == NULL) return -1;
    size_t n = fwrite(p, sizeof *p, 1, f);
    fclose(f);
    return n == 1 ? 0 : -1;
}
```

This is `io3`.

## `fseek`, `ftell` and the size of a file

`fseek` moves the cursor, `ftell` gives its position in bytes.

```c
fseek(f, 0, SEEK_END);   // go to the end
long taille = ftell(f);  // number of bytes
rewind(f);               // back to the beginning: fseek(f, 0, SEEK_SET)
```

`ftell` can fail (`-1`): check the value before using it. This is
`errors2`.

## End of file and errors

- `fgets` returns `NULL` at end of file **or** on error; distinguish with
  `feof(f)` and `ferror(f)`.
- `getchar()` returns `EOF` (a negative value, not a `char`) at the end;
  always compare against an `int`, never against a `char`.
- After a write error, remember to `fclose` anyway.

## C-style error handling

No exceptions: the convention is "return value = status", and `errno`
(in `<errno.h>`) says why the system call failed.

```c
#include <errno.h>

errno = 0;
FILE *f = fopen("/aucun/fichier", "r");
if (f == NULL) {
    perror("fopen");                          // "fopen: No such file or directory"
    fprintf(stderr, "%s\n", strerror(errno)); // the message alone
}
```

- `errno` is read **only** if the call reported an error;
- we reset `errno = 0` before a call that can return a legitimate value
  indistinguishable from an error;
- `perror` adds the system message, `strerror(errno)` gives it alone.

## `strtol`: converting with control

`atoi` signals nothing. `strtol` is the safe version:

```c
#include <stdlib.h>
#include <errno.h>

errno = 0;
char *fin;
long v = strtol(s, &fin, 10);   // base 10

if (fin == s) {
    /* no digit read: invalid input */
} else if (*fin != '\0') {
    /* stray characters after the number */
} else if (errno == ERANGE) {
    /* overflow of the range of a long */
}
/* here: success, v is valid */
```

`strtol` skips whitespace, accepts a `+`/`-`, reads the digits, then sets `fin`
to the first **unconsumed** character. If no digit is read, `fin` stays
equal to `s`. `ERANGE` (in `<errno.h>`) signals the overflow. This is `errors1`
and `errors3`.

## The takeaway

Every `fopen` has its `fclose`, every read tests its return value, and
`errno` is read only after a **reported** failure. To convert text into a
number: `strtol` with `endptr` and `ERANGE`, never `atoi`.

Related exercises: `io1`..`io3`, `errors1`..`errors3`.
