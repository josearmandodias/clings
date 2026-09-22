# Contributing to clings

[Français](CONTRIBUTING.md) · **English**

Thanks for your interest! This repo is a course of C exercises: each exercise
is a small broken program that the learner repairs. The whole value of the
course rests on one simple rule, and everything else follows from it:

> **the solution compiles and passes; the statement, with the marker removed,
> fails.**

## Prerequisites

```sh
bash --version     # any version >= 3.2
cc --version       # clang or gcc
git --version
```

Nothing to install. The sanitizers (ASan/UBSan) are detected automatically.

## Anatomy of an exercise

Three files, plus any extra files:

```
exercises/<section>/<name>.c    the statement (what the learner sees)
hints/<name>.txt                the hint
solutions/<name>.c              the fix
```

and a line in `exercises/order.txt`.

The `<name>` must be **unique across the whole repo**: it names the binary, the
solution and the hint.

A statement looks like this:

```c
// One sentence about the concept, then what is broken.
//
// `doubler` must return twice its argument.


// I AM NOT DONE

#include "clings.h"

int doubler(int x)
{
    /* TODO */
    (void)x;
    return x;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(doubler(2) == 4);
    OK("doubler");
    return 0;
}
```

Key points:

- the `// I AM NOT DONE` line **must** be in the statement and **never** in the
  solution: it is what marks the exercise as "to do";
- everything after `NE TOUCHE PAS` is the test, and must be **identical** in
  the statement and in the solution;
- `main` ends with `return 0;` and an `OK(...)`.

## The golden rules

1. **The solution compiles without error or warning and passes**, with:
   `-std=c17 -Wall -Wextra -Werror -Wshadow -g -fsanitize=address,undefined`.
2. **The statement, once the marker is removed, fails** (compilation or
   execution). A statement that already passes is worth nothing.
3. No warnings: `-Wextra` forbids unused parameters (use `(void)x;` in the
   stubs).

## Adding an exercise, step by step

1. Create `exercises/<section>/<name>.c` (the broken statement),
   `solutions/<name>.c` (the fix) and `hints/<name>.txt` (the hint).
2. Add the relative path to `exercises/` in `exercises/order.txt`, at the
   place where the exercise should appear.
3. Regenerate the local blank copy then check:

```sh
rm -rf .templates          # to start from a clean state
./clings help >/dev/null   # recreates .templates from exercises/
./dev/check.sh <name>       # or without an argument to check everything
```

4. Open a pull request. CI runs `dev/check.sh` on macOS and Ubuntu, and tells
   you whether everything is good.

## The template trap

`.templates/` is **gitignored**: it is a local cache used by `clings reset`. It
is created on first launch, and only if it does not exist. If you modify an
existing statement, remember to:

```sh
rm -rf .templates && ./clings help >/dev/null
```

Otherwise `reset` would restore the old version and `dev/check.sh` would report
a desynchronized template.

## Multi-file exercises

The extra files of an exercise `<name>` are named `<name>_something.c` (or
`.h`) and live in the same folder. `clings` automatically compiles
`exercises/<section>/<name>_*.c`. In `solutions/`, put only the files the
learner has to modify; the unchanged extras are taken from `exercises/`.

Example: `modules2.c` + `modules2_table.c` (provided) + `modules2_table.h`
(to fix).

## Style

- French, in the tone of the existing exercises; accents are welcome.
- The statement explains the concept and the trap, without giving the answer.
- The hint guides toward the solution, without copying it.
- End the tests with an `OK("short message")`.
- Format your code like the neighboring files (4-space indentation).

## Memory

An exercise that allocates starts with:

```c
#define CLINGS_TRACK_ALLOC
#include "clings.h"
```

and ends with `CHECK_NO_LEAK();` before the `OK(...)`. The harness then counts
allocations and fails if any remain.

## Reporting a problem

Open an issue specifying the exercise (`./clings run <name>`), what you got,
what you expected, and your platform. An ambiguous exercise or a misleading
hint is a real bug.

## License

By contributing, you agree that your contribution will be published under the
MIT license.
