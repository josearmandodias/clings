# clings

[![check](https://github.com/josearmandodias/clings/actions/workflows/check.yml/badge.svg)](https://github.com/josearmandodias/clings/actions/workflows/check.yml) [![PRs welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.en.md)

[Français](README.md) · **English**

Small exercises to learn C, in the spirit of [rustlings](https://rustlings.rust-lang.org/).

109 exercises, each in a broken or incomplete `.c` file. You fix it, you save,
and it reruns on its own.

## Getting started

```sh
git clone https://github.com/josearmandodias/clings.git
cd clings
./clings
```

That's it. No dependencies: bash and a C compiler (`clang` on macOS, `gcc` on
Linux). Watch mode shows the current exercise, recompiles it on every save and
moves on to the next one once it passes.

An exercise is done when it compiles, its tests pass, **and** you have removed
the `// I AM NOT DONE` comment at the top of the file.

## Commands

| Command | Effect |
|---|---|
| `./clings` | watch mode (the normal mode) |
| `./clings run <name>` | run one specific exercise |
| `./clings list` | status of all exercises |
| `./clings hint <name>` | hint |
| `./clings solution <name>` | one possible solution |
| `./clings reset <name>` | restore the original statement (file and extras) |
| `./clings verify` | check everything |

## What runs under the hood

Each file is compiled with:

```
-std=c17 -Wall -Wextra -Werror -Wshadow -g
-fsanitize=address,undefined
```

`-Werror` turns every warning into an error. This is deliberate: in C, a
warning is almost always a bug biding its time.

AddressSanitizer and UndefinedBehaviorSanitizer are the real reason this repo
exists. Without them, an array overflow produces a silent `Segmentation fault`,
or worse, nothing at all. With them, you get the file, the line, the exact
nature of the error and the call stack. That is what replaces, as well as it
can, the Rust compiler's messages.

The sanitizers are detected automatically; if your compiler does not support
them, the exercises still run.

For memory leaks, `clings.h` counts calls to `malloc`/`free` and
`CHECK_NO_LEAK()` fails if any blocks remain. This homegrown counter is mostly
useful on macOS, where LeakSanitizer does not exist.

## Progression

| Section | Contents |
|---|---|
| `00_intro` | getting started, reading a compilation error |
| `01_types` | `printf` formats, signed/unsigned, integer division, overflow, floating point, `enum` |
| `02_pointers` | address and dereference, passing by address, output parameters, `const`, arithmetic, function pointers, `void *` |
| `03_arrays` | array decay, out-of-bounds, 2D arrays, rotation, binary search, `memmove` |
| `04_strings` | the null byte, bounded writing, rewriting `strlen`/`strcpy`/`strcmp`/`strchr`, counting words, palindrome |
| `05_memory` | stack vs heap, leaks, use-after-free, double free, `calloc`, dynamic matrices, ownership, deep copy |
| `06_structs` | copy, pointers and `->`, `qsort`, nested structs, unions, padding, function pointers |
| `07_modules` | separate compilation, headers, include guards, preprocessor (`#`, `##`, `#if`) |
| `08_io` | reading and writing files, binary, `errno`, `strtol` |
| `09_recursion` | factorial, fast power, gcd, Hanoi, digit sum, binary search, palindrome |
| `10_datastructures` | stack, circular queue, linked lists, binary search tree, hash table |
| `11_bitwise` | manipulating bits, masks and flags, popcount, binary, endianness, bit fields |
| `12_tri` | insertion, merge, quick and counting sorts |
| `13_linked_lists` | search and k-th, insert at index, delete, recursive reversal, merge sorted lists, middle and Floyd's cycle, duplicates, deep copy |

The order is the one in `exercises/order.txt`. Adding an exercise: create the
`.c`, add it to that file, and drop in a `hints/<name>.txt` and a
`solutions/<name>.c`.

## Cheat sheets

Each section of the course has its cheat sheet: a reference **and** a mind map,
in French and English. Full index in [`fiches/`](fiches/README.md).

- [`intro.md`](fiches/en/intro.md) — compiling, running, reading errors
- [`types.md`](fiches/en/types.md) — integers, conversions, floating point, `printf`
- [`pointers.md`](fiches/en/pointers.md) — operators, `const`, arithmetic, function pointers, `void *`
- [`arrays.md`](fiches/en/arrays.md) — decay, bounds, 2D arrays, binary search
- [`strings.md`](fiches/en/strings.md) — `'\0'`, bounded writing, traversal
- [`memory.md`](fiches/en/memory.md) — stack and heap, `malloc`, ownership, leaks
- [`structs.md`](fiches/en/structs.md) — copy, `->`, padding, unions, `qsort`
- [`modules.md`](fiches/en/modules.md) — separate compilation, headers, preprocessor
- [`io.md`](fiches/en/io.md) — files, text and binary, `errno`, `strtol`
- [`recursion.md`](fiches/en/recursion.md) — base case, call stack, algorithms
- [`structures.md`](fiches/en/structures.md) — lists, stack, queue, tree, hashing
- [`bitwise.md`](fiches/en/bitwise.md) — masks, shifts, endianness
- [`sorting.md`](fiches/en/sorting.md) — insertion, merge, quick, counting

## Writing an exercise

An exercise is a standalone program. It includes `clings.h`, which provides:

- `CHECK(cond)` — fails cleanly with the file and the line
- `OK("message")` — prints a success line
- `CHECK_NO_LEAK()` — checks that no block is still allocated
  (requires `#define CLINGS_TRACK_ALLOC` before the include)

The block below the `NE TOUCHE PAS` line holds the tests: that is what defines
the exercise, and the learner does not modify it.

On first launch, `clings` copies the statements into `.templates/` (gitignored);
that is what `reset` restores. Both the `.c` **and** the `.h` files are captured,
because some exercises (`07_modules`) require fixing a header.

## Development

`dev/check.sh` validates the integrity of the course:

```sh
./dev/check.sh          # the 109 exercises
./dev/check.sh arrays7  # just one
```

For each exercise it checks that the statement, the hint, the solution and the
blank copy exist, that **the solution compiles and passes**, and that **the
statement, with the marker removed, fails** (otherwise the exercise would
already be solved). Run it after adding or modifying an exercise.

## Contributing

Contributions are welcome: a new exercise, a clearer wording for an ambiguous
one, a better hint, a cheat sheet, or an improvement to the harness.

- Open an *issue* to report an unclear exercise or a bug.
- Open a *pull request* to propose a change: CI runs `dev/check.sh` on macOS
  and Ubuntu and tells you whether everything holds.
- The step-by-step guide (anatomy of an exercise, golden rules, the templates
  trap, style) is in [`CONTRIBUTING.en.md`](CONTRIBUTING.en.md).

An ambiguous exercise or a misleading hint is a real bug: don't hesitate.

## License

MIT — see [`LICENSE`](LICENSE).
