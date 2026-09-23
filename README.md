# clings

[![check](https://github.com/josearmandodias/clings/actions/workflows/check.yml/badge.svg)](https://github.com/josearmandodias/clings/actions/workflows/check.yml) [![PRs welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)

**Français** · [English](README.en.md)

> rustlings, mais pour le C.

clings est un ensemble d'exercices de C. Chaque exercice est un fichier `.c`
cassé ou incomplet : soit il ne compile pas, soit ses tests échouent. Il faut le
réparer.

109 exercices, répartis en 14 sections.

## Démarrer

```sh
git clone https://github.com/josearmandodias/clings.git
cd clings
./clings
```

`./clings` lance le mode watch : l'exercice courant s'affiche, est recompilé à
chaque sauvegarde, et le suivant s'ouvre quand il est validé.

Prérequis : bash et un compilateur C (`clang` ou `gcc`). Aucune autre
dépendance.

## Valider un exercice

Un exercice est terminé quand :

1. le fichier compile sans warning ;
2. ses tests passent ;
3. la ligne `// I AM NOT DONE` a été retirée.

## Commandes

| Commande | Effet |
|---|---|
| `./clings` | mode watch |
| `./clings run <nom>` | exécute un exercice |
| `./clings list` | liste les exercices et leur état |
| `./clings hint <nom>` | affiche l'indice |
| `./clings solution <nom>` | affiche une solution |
| `./clings reset <nom>` | restaure l'énoncé d'origine |
| `./clings verify` | exécute tous les exercices |

## Compilation

Chaque fichier est compilé avec :

```
-std=c17 -Wall -Wextra -Werror -Wshadow -g
-fsanitize=address,undefined
```

`-Werror` transforme chaque warning en erreur. Les sanitizers sont détectés au
démarrage ; s'ils ne sont pas disponibles, la compilation se fait sans eux.

`include/clings.h` fournit le harnais des tests :

- `CHECK(cond)` — échoue avec le fichier et la ligne ;
- `OK("message")` — affiche une ligne de succès ;
- `CHECK_NO_LEAK()` — compare les appels à `malloc` et `free`
  (nécessite `#define CLINGS_TRACK_ALLOC`).

## Sections

`00_intro` · `01_types` · `02_pointers` · `03_arrays` · `04_strings` ·
`05_memory` · `06_structs` · `07_modules` · `08_io` · `09_recursion` ·
`10_datastructures` · `11_bitwise` · `12_tri` · `13_linked_lists`

Chaque section a une fiche (aide-mémoire et carte mentale, en français et en
anglais) : [`fiches/`](fiches/README.md).

## Écrire un exercice

Un exercice est un programme autonome qui inclut `clings.h`. Les tests sont sous
la ligne `NE TOUCHE PAS` et ne sont pas modifiés par l'apprenant.

Pour en ajouter un : créer `exercises/<section>/<nom>.c`, l'ajouter à
`exercises/order.txt`, puis créer `hints/<nom>.txt` et `solutions/<nom>.c`.

## Développement

`dev/check.sh` vérifie que chaque solution compile et passe, et que chaque
énoncé échoue :

```sh
./dev/check.sh
./dev/check.sh arrays7
```

## Contribuer

Voir [`CONTRIBUTING.md`](CONTRIBUTING.md).

## Licence

MIT — voir [`LICENSE`](LICENSE).
