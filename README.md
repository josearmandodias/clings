# clings

Petits exercices pour apprendre le C, dans l'esprit de [rustlings](https://rustlings.rust-lang.org/).

109 exercices, chacun dans un fichier `.c` cassé ou incomplet. Tu le répares,
tu sauvegardes, ça se relance tout seul.

## Démarrer

```sh
./clings
```

C'est tout. Pas de dépendance : bash et un compilateur C (`clang` sur macOS,
`gcc` sur Linux). Le mode watch affiche l'exercice courant, le recompile à
chaque sauvegarde et passe au suivant quand il est validé.

Un exercice est terminé quand il compile, que ses tests passent, **et** que tu
as retiré le commentaire `// I AM NOT DONE` en tête de fichier.

## Commandes

| Commande | Effet |
|---|---|
| `./clings` | mode watch (le mode normal) |
| `./clings run <nom>` | lance un exercice précis |
| `./clings list` | état de tous les exercices |
| `./clings hint <nom>` | indice |
| `./clings solution <nom>` | une solution possible |
| `./clings reset <nom>` | restaure l'énoncé d'origine (fichier et annexes) |
| `./clings verify` | vérifie tout |

## Ce qui tourne sous le capot

Chaque fichier est compilé avec :

```
-std=c17 -Wall -Wextra -Werror -Wshadow -g
-fsanitize=address,undefined
```

`-Werror` transforme chaque avertissement en erreur. C'est volontaire : en C,
un warning est presque toujours un bug qui attend son heure.

AddressSanitizer et UndefinedBehaviorSanitizer sont la vraie raison d'être de
ce dépôt. Sans eux, un dépassement de tableau produit un `Segmentation fault`
muet, ou pire, rien du tout. Avec eux, tu obtiens le fichier, la ligne, la
nature exacte de l'erreur et la pile d'appels. C'est ce qui remplace, tant bien
que mal, les messages du compilateur Rust.

Les sanitizers sont détectés automatiquement ; si ton compilateur ne les
supporte pas, les exercices tournent quand même.

Pour les fuites mémoire, `clings.h` compte les appels à `malloc`/`free` et
`CHECK_NO_LEAK()` échoue s'il reste des blocs. Ce compteur maison sert surtout
sur macOS, où LeakSanitizer n'existe pas.

## Progression

| Section | Contenu |
|---|---|
| `00_intro` | prise en main, lire une erreur de compilation |
| `01_types` | formats `printf`, signé/non signé, division entière, débordement, flottants, `enum` |
| `02_pointers` | adresse et déréférencement, passage par adresse, paramètres de sortie, `const`, arithmétique, pointeurs de fonction, `void *` |
| `03_arrays` | array decay, dépassement de borne, tableaux 2D, rotation, recherche binaire, `memmove` |
| `04_strings` | l'octet nul, écriture bornée, réécrire `strlen`/`strcpy`/`strcmp`/`strchr`, compter les mots, palindrome |
| `05_memory` | pile vs tas, fuites, use-after-free, double free, `calloc`, matrices dynamiques, propriété, copie profonde |
| `06_structs` | copie, pointeurs et `->`, `qsort`, structures imbriquées, unions, padding, pointeurs de fonction |
| `07_modules` | compilation séparée, headers, gardes d'inclusion, préprocesseur (`#`, `##`, `#if`) |
| `08_io` | lecture et écriture de fichiers, binaire, `errno`, `strtol` |
| `09_recursion` | factorielle, puissance rapide, pgcd, Hanoï, somme des chiffres, recherche binaire, palindrome |
| `10_datastructures` | pile, file circulaire, listes chaînées, arbre binaire de recherche, table de hachage |
| `11_bitwise` | manipuler les bits, masques et drapeaux, popcount, binaire, boutisme, champs de bits |
| `12_tri` | tris par insertion, fusion, rapide et comptage |
| `13_linked_lists` | recherche et k-ième, insertion à l'index, suppression, inversion récursive, fusion de listes triées, milieu et cycle de Floyd, doublons, copie profonde |

L'ordre est celui de `exercises/order.txt`. Ajouter un exercice : créer le
`.c`, l'ajouter à ce fichier, et déposer un `hints/<nom>.txt` et une
`solutions/<nom>.c`.

## Fiches

Des fiches de référence, à consulter quand un thème te résiste :

- [`pointeurs-c.md`](pointeurs-c.md) — opérateurs, `const`, arithmétique,
  pointeurs de fonction, `void *`, propriété
- [`structures-c.md`](structures-c.md) — listes chaînées, pile, file, arbre
  binaire de recherche, table de hachage
- [`bitwise-c.md`](bitwise-c.md) — représentation, décalages, masques,
  popcount, boutisme, pièges

## Écrire un exercice

Un exercice est un programme autonome. Il inclut `clings.h`, qui fournit :

- `CHECK(cond)` — échoue proprement avec le fichier et la ligne
- `OK("message")` — affiche une ligne de succès
- `CHECK_NO_LEAK()` — vérifie qu'aucun bloc n'est resté alloué
  (nécessite `#define CLINGS_TRACK_ALLOC` avant l'inclusion)

Le bloc sous la ligne `NE TOUCHE PAS` contient les tests : c'est ce qui
définit l'exercice, l'apprenant ne le modifie pas.

Au premier lancement, `clings` recopie les énoncés dans `.templates/` (ignoré
par git) ; c'est ce que `reset` restaure. Les `.c` **et** les `.h` sont
capturés, car certains exercices (`07_modules`) demandent de corriger un
header.

## Développer

`dev/check.sh` valide l'intégrité du cours :

```sh
./dev/check.sh          # les 109 exercices
./dev/check.sh arrays7  # un seul
```

Pour chaque exercice il vérifie que l'énoncé, l'indice, la solution et la copie
vierge existent, que **la solution compile et passe**, et que **l'énoncé,
marqueur retiré, échoue** (sinon l'exercice serait déjà résolu). Lance-le après
avoir ajouté ou modifié un exercice.

## Licence

MIT — voir [`LICENSE`](LICENSE).
