# Compiling, running, reading errors — cheat sheet

In C there is no interpreter and no REPL: you edit a source file, you translate
it into a binary, then you run it. This cycle is your basic tool, and the
compiler message is text to read, not a punishment. This cheat sheet
accompanies the `00_intro` chapter.

## The cycle: edit, save, run again

```sh
cc -std=c17 -Wall -Wextra -Werror -g prog.c -o prog   # compile
./prog                                                 # run
```

- `cc` picks the system compiler (clang on macOS, gcc on Linux);
- `-std=c17` fixes the language version;
- `-Wall -Wextra` enable the warnings, `-Werror` turns them into errors;
- `-g` keeps the variable names for the debugger and the sanitizers;
- `-o prog` names the executable (without `-o`, an `a.out` shows up).

Compiling and running are two distinct steps. A program can compile without a
single error and crash at runtime: the compiler only sees types, the runtime
sees values.

## Reading an error message

Classic format of a diagnostic:

```
prog.c:20:5: error: expected ';' after expression
    somme = a + b;
    ^
1 error generated.
```

From left to right:

1. `prog.c`: the faulty file;
2. `20`: the line;
3. `5`: the column, often the start of the word at fault;
4. `error:`: the severity, followed by the message;
5. the echoed line, with a `^` aligned on the column.

A single missing `;` can produce dozens of cascading messages: the second
"error" is often a consequence of the first. Always fix the **first** one,
recompile, and watch how many disappear. This is exactly the `intro2` exercise.

Order of severity: `error:` prevents generating the binary; `warning:` lets it
compile but flags a likely bug. With `-Werror`, a warning becomes an error, so
nothing comes out. That is intentional.

## The `// I AM NOT DONE` line

Every statement starts marked:

```c
// I AM NOT DONE
```

This is the "to do" checkbox. `clings` considers the exercise finished when
three conditions are met: it compiles, its tests pass, and this comment has
disappeared. Removing the marker without the tests passing is pointless; the
message will remind you.

## The harness: `CHECK` and `OK`

```c
CHECK(somme == 42);        // the test must be true, otherwise failure
OK("premier exercice");    // success line
```

- `CHECK(cond)`: if `cond` is false, prints
  `[X] test echoue : ... (fichier ligne N)` and exits with code 1;
- `OK("...")`: prints `[v] message`, then execution continues;
- `CHECK_NO_LEAK()` (after `#define CLINGS_TRACK_ALLOC`) counts the
  `malloc`/`free` and fails if a block is left.

The block under `// ---------------------------- NE TOUCHE PAS -----------------------------`
contains the tests: never touch it.

## The `./clings` flow

```sh
./clings              # watch: the current exercise, rerun on every save
./clings run types3   # a specific exercise
./clings list         # the state of all the exercises
./clings hint types3  # a hint
./clings solution types3
./clings reset types3
./clings verify
```

In watch mode, you launch `./clings` once and never touch the terminal again:
on every save, the exercise is recompiled and progress advances on its own.
The files are compiled with `-std=c17 -Wall -Wextra -Werror -Wshadow -g`,
plus the sanitizers when they are available.

## What ASan and UBSan are for

C checks almost nothing at runtime; the sanitizers fill this gap and
play a bit the role of Rust's messages.

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```

| Tool | What it catches |
|---|---|
| AddressSanitizer (ASan) | out-of-bounds read/write, use-after-free, double free |
| UndefinedBehaviorSanitizer (UBSan) | signed overflow, division by zero, invalid shift, misalignment |

Without them, an array overrun writes silently into the neighbouring memory
and the bug blows up elsewhere, later. With them, you get the file, the line and
the exact nature of the fault — as in `arrays2` and `arrays9`.

Memory leaks, for their part, are covered by `CHECK_NO_LEAK()`: the
home-made counter of `clings.h`, useful in particular on macOS where LeakSanitizer
does not exist.

## The takeaway

A single rule: **save, read the first error, fix only that one,
start over.** The compiler is your first proofreader; ASan and UBSan are the
second.

Related exercises: `intro1`, `intro2`.
