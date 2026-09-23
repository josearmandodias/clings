# clings

[![check](https://github.com/josearmandodias/clings/actions/workflows/check.yml/badge.svg)](https://github.com/josearmandodias/clings/actions/workflows/check.yml) [![PRs welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.en.md)

[Français](README.md) · **English**

> rustlings, but for C.

clings is a set of C exercises. Each exercise is a `.c` file that is broken or
incomplete: either it does not compile, or its tests fail. Your job is to fix it.

109 exercises, split across 14 sections.

## Getting started

```sh
git clone https://github.com/josearmandodias/clings.git
cd clings
./clings
```

`./clings` starts watch mode: the current exercise is shown, recompiled on every
save, and the next one opens once it passes.

Requirements: bash and a C compiler (`clang` or `gcc`). Nothing else.

## Passing an exercise

An exercise is done when:

1. the file compiles without warnings;
2. its tests pass;
3. the `// I AM NOT DONE` line has been removed.

## Commands

| Command | Effect |
|---|---|
| `./clings` | watch mode |
| `./clings run <name>` | run one exercise |
| `./clings list` | list exercises and their status |
| `./clings hint <name>` | show the hint |
| `./clings solution <name>` | show one solution |
| `./clings reset <name>` | restore the original statement |
| `./clings verify` | run every exercise |

## Compilation

Each file is compiled with:

```
-std=c17 -Wall -Wextra -Werror -Wshadow -g
-fsanitize=address,undefined
```

`-Werror` turns every warning into an error. Sanitizers are detected at startup;
if they are not available, compilation proceeds without them.

`include/clings.h` provides the test harness:

- `CHECK(cond)` — fails with the file and line;
- `OK("message")` — prints a success line;
- `CHECK_NO_LEAK()` — compares calls to `malloc` and `free`
  (requires `#define CLINGS_TRACK_ALLOC`).

## Sections

`00_intro` · `01_types` · `02_pointers` · `03_arrays` · `04_strings` ·
`05_memory` · `06_structs` · `07_modules` · `08_io` · `09_recursion` ·
`10_datastructures` · `11_bitwise` · `12_tri` · `13_linked_lists`

Each section has a cheat sheet (reference and mind map, in French and English):
[`fiches/`](fiches/README.md).

## Writing an exercise

An exercise is a standalone program that includes `clings.h`. The tests live
below the `NE TOUCHE PAS` line and are not modified by the learner.

To add one: create `exercises/<section>/<name>.c`, add it to
`exercises/order.txt`, then create `hints/<name>.txt` and `solutions/<name>.c`.

## Development

`dev/check.sh` checks that every solution compiles and passes, and that every
statement fails:

```sh
./dev/check.sh
./dev/check.sh arrays7
```

## Contributing

See [`CONTRIBUTING.en.md`](CONTRIBUTING.en.md).

## License

MIT — see [`LICENSE`](LICENSE).
