# Compiler, exécuter, lire les erreurs — fiche

En C, il n'y a ni interpréteur ni REPL : tu édites un fichier source, tu le
traduis en binaire, puis tu l'exécutes. Ce cycle est ton outil de base, et le
message du compilateur est un texte à lire, pas une sanction. Cette fiche
accompagne le chapitre `00_intro`.

## Le cycle : éditer, sauvegarder, relancer

```sh
cc -std=c17 -Wall -Wextra -Werror -g prog.c -o prog   # compiler
./prog                                                 # exécuter
```

- `cc` choisit le compilateur du système (clang sur macOS, gcc sur Linux) ;
- `-std=c17` fixe la version du langage ;
- `-Wall -Wextra` activent les avertissements, `-Werror` les transforme en erreurs ;
- `-g` garde les noms de variables pour le débogueur et les sanitizers ;
- `-o prog` nomme l'exécutable (sans `-o`, un `a.out` apparaît).

Compiler et exécuter sont deux étapes distinctes. Un programme peut se compiler
sans une seule erreur et planter à l'exécution : le compilateur ne voit que des
types, l'exécution voit des valeurs.

## Lire un message d'erreur

Format classique d'un diagnostic :

```
prog.c:20:5: error: expected ';' after expression
    somme = a + b;
    ^
1 error generated.
```

De gauche à droite :

1. `prog.c` : le fichier fautif ;
2. `20` : la ligne ;
3. `5` : la colonne, souvent le début du mot en cause ;
4. `error:` : la gravité, suivie du message ;
5. la ligne recopiée, avec un `^` aligné sur la colonne.

Un seul `;` manquant peut produire des dizaines de messages en cascade : la
deuxième « erreur » est souvent une conséquence de la première. Corrige toujours
la **première**, recompile, et regarde combien disparaissent. C'est exactement
l'exercice `intro2`.

Ordre de gravité : `error:` empêche la génération du binaire ; `warning:` laisse
compiler mais signale un bug probable. Avec `-Werror`, un warning devient une
erreur, donc rien ne sort. C'est volontaire.

## La ligne `// I AM NOT DONE`

Chaque énoncé commence marqué :

```c
// I AM NOT DONE
```

C'est la coche « à faire ». `clings` considère l'exercice terminé quand trois
conditions sont réunies : il compile, ses tests passent, et ce commentaire a
disparu. Retirer le marqueur sans que les tests passent ne sert à rien, le
message te le rappellera.

## Le harnais : `CHECK` et `OK`

```c
CHECK(somme == 42);        // le test doit être vrai, sinon échec
OK("premier exercice");    // ligne de succès
```

- `CHECK(cond)` : si `cond` est fausse, affiche
  `[X] test echoue : ... (fichier ligne N)` et termine avec le code 1 ;
- `OK("...")` : affiche `[v] message`, puis on continue ;
- `CHECK_NO_LEAK()` (après `#define CLINGS_TRACK_ALLOC`) compte les
  `malloc`/`free` et échoue s'il reste un bloc.

Le bloc sous `// ---------------------------- NE TOUCHE PAS -----------------------------`
contient les tests : on n'y touche jamais.

## Le flux `./clings`

```sh
./clings              # watch : l'exercice courant, relancé à chaque sauvegarde
./clings run types3   # un exercice précis
./clings list         # l'état de tous les exercices
./clings hint types3  # un indice
./clings solution types3
./clings reset types3
./clings verify
```

En mode watch, tu lances `./clings` une fois et tu ne touches plus au terminal :
à chaque sauvegarde, l'exercice est recompilé et la progression avance seule.
Les fichiers sont compilés avec `-std=c17 -Wall -Wextra -Werror -Wshadow -g`,
plus les sanitizers s'ils sont disponibles.

## À quoi servent ASan et UBSan

Le C ne vérifie presque rien à l'exécution ; les sanitizers comblent ce trou et
jouent un peu le rôle des messages de Rust.

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```

| Outil | Ce qu'il attrape |
|---|---|
| AddressSanitizer (ASan) | lecture/écriture hors bornes, use-after-free, double free |
| UndefinedBehaviorSanitizer (UBSan) | débordement signé, division par zéro, décalage invalide, mauvais alignement |

Sans eux, un dépassement de tableau écrit silencieusement dans la mémoire voisine
et le bug éclate ailleurs, plus tard. Avec eux, tu obtiens le fichier, la ligne et
la nature exacte de la faute — comme dans `arrays2` et `arrays9`.

Les fuites mémoire, elles, sont couvertes par `CHECK_NO_LEAK()` : le compteur
maison de `clings.h`, utile notamment sur macOS où LeakSanitizer n'existe pas.

## Le réflexe

Une seule règle : **sauvegarde, lis la première erreur, corrige-la seule,
recommence.** Le compilateur est ton premier relecteur ; ASan et UBSan sont le
second.

Exercices liés : `intro1`, `intro2`.
