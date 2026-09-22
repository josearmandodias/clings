# Contribuer à clings

Merci de t'y intéresser ! Ce dépôt est un cours d'exercices de C : chaque
exercice est un petit programme cassé que l'apprenant répare. Toute la valeur
du cours tient à une règle simple, et le reste en découle :

> **la solution compile et passe ; l'énoncé, marqueur retiré, échoue.**

## Prérequis

```sh
bash --version     # n'importe quelle version >= 3.2
cc --version       # clang ou gcc
git --version
```

Aucune dépendance à installer. Les sanitizers (ASan/UBSan) sont détectés
automatiquement.

## Anatomie d'un exercice

Trois fichiers, plus d'éventuelles annexes :

```
exercises/<section>/<nom>.c    l'énoncé (ce que voit l'apprenant)
hints/<nom>.txt                l'indice
solutions/<nom>.c              la correction
```

et une ligne dans `exercises/order.txt`.

Le `<nom>` doit être **unique dans tout le dépôt** : il nomme le binaire, la
solution et l'indice.

Un énoncé ressemble à ceci :

```c
// Une phrase sur la notion, puis ce qui est cassé.
//
// `doubler` doit renvoyer le double de son argument.


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

Points clés :

- la ligne `// I AM NOT DONE` **doit** être dans l'énoncé et **jamais** dans la
  solution : c'est elle qui marque l'exercice « à faire » ;
- tout ce qui suit `NE TOUCHE PAS` est le test, et doit être **identique** dans
  l'énoncé et dans la solution ;
- `main` se termine par `return 0;` et un `OK(...)`.

## Les règles d'or

1. **La solution compile sans erreur ni warning et passe**, avec :
   `-std=c17 -Wall -Wextra -Werror -Wshadow -g -fsanitize=address,undefined`.
2. **L'énoncé, une fois le marqueur retiré, échoue** (compilation ou exécution).
   Un énoncé qui passe déjà ne vaut rien.
3. Pas de warning : `-Wextra` interdit les paramètres inutilisés (utilise
   `(void)x;` dans les squelettes).

## Ajouter un exercice, pas à pas

1. Crée `exercises/<section>/<nom>.c` (l'énoncé cassé), `solutions/<nom>.c` (la
   correction) et `hints/<nom>.txt` (l'indice).
2. Ajoute le chemin relatif à `exercises/` dans `exercises/order.txt`, à
   l'endroit où l'exercice doit apparaître.
3. Régénère la copie vierge locale puis vérifie :

```sh
rm -rf .templates          # pour repartir d'un état propre
./clings help >/dev/null   # recrée .templates depuis exercises/
./dev/check.sh <nom>       # ou sans argument pour tout vérifier
```

4. Ouvre une pull request. La CI lance `dev/check.sh` sur macOS et Ubuntu, et
   t'indique si tout est bon.

## Le piège des templates

`.templates/` est **ignoré par git** : c'est un cache local qui sert à
`clings reset`. Il est créé au premier lancement, et seulement s'il n'existe
pas. Si tu modifies un énoncé existant, pense à :

```sh
rm -rf .templates && ./clings help >/dev/null
```

Sinon `reset` restaurerait l'ancienne version et `dev/check.sh` signalerait un
template désynchronisé.

## Exercices multi-fichiers

Les annexes d'un exercice `<nom>` se nomment `<nom>_quelquechose.c` (ou `.h`)
et vivent dans le même dossier. `clings` compile automatiquement
`exercises/<section>/<nom>_*.c`. Dans `solutions/`, ne dépose que les fichiers
que l'apprenant doit modifier ; les annexes inchangées sont prises dans
`exercises/`.

Exemple : `modules2.c` + `modules2_table.c` (fourni) + `modules2_table.h`
(à corriger).

## Style

- Français, dans le ton des exercices existants ; les accents sont bienvenus.
- L'énoncé explique la notion et le piège, sans donner la réponse.
- L'indice guide vers la solution, sans la recopier.
- Termine les tests par un `OK("message court")`.
- Formate ton code comme les fichiers voisins (indentation de 4 espaces).

## Mémoire

Un exercice qui alloue commence par :

```c
#define CLINGS_TRACK_ALLOC
#include "clings.h"
```

et se termine par `CHECK_NO_LEAK();` avant le `OK(...)`. Le harnais compte
alors les allocations et échoue s'il en reste.

## Signaler un problème

Ouvre une issue en précisant l'exercice (`./clings run <nom>`), ce que tu
obtenais, ce que tu attendais, et ta plateforme. Un exercice ambigu ou un
indice trompeur est un vrai bug.

## Licence

En contribuant, tu acceptes que ta contribution soit publiée sous licence MIT.
