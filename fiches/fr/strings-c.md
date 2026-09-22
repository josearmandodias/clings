# Les chaînes en C — fiche

Une chaîne C n'est pas un type du langage : c'est un tableau de `char` terminé
par un octet nul `'\0'`. Toutes les fonctions de `<string.h>` s'arrêtent à cet
octet ; s'il manque, elles lisent au-delà du tableau. Cette fiche accompagne le
chapitre `04_strings`.

## `char` et l'octet nul

```c
char c = 'A';        // un caractère, de code 65
char s[] = "ABC";    // { 'A', 'B', 'C', '\0' } : 4 octets
```

`'A'` est un `int` valant le code du caractère ; `"A"` est une chaîne (2 octets).
La longueur au sens de `strlen` ne compte **pas** le `'\0'`. Une chaîne de `n`
caractères occupe donc toujours `n + 1` octets.

## Littéral en lecture seule ou tableau modifiable

```c
char  *p = "bonjour";   // p pointe sur un littéral, souvent en lecture seule
char  t[] = "bonjour";  // t copie les 8 octets dans un tableau modifiable

t[0] = 'B';             // OK
p[0] = 'B';             // UB : segfault à l'exécution
```

Un littéral a beau avoir un type proche de `char[]`, modifier son contenu est un
comportement indéfini. Dès que tu dois écrire dedans, déclare un **tableau**.
C'est l'exercice `strings4`.

## Les fonctions essentielles

| Fonction | Rôle | Renvoie |
|---|---|---|
| `strlen(s)` | longueur hors `'\0'` | `size_t` |
| `strcpy(dst, src)` | copie toute la chaîne | `dst` |
| `strncpy(dst, src, n)` | copie au plus `n` octets | `dst` |
| `strcmp(a, b)` | compare | `< 0`, `0`, `> 0` |
| `strchr(s, c)` | cherche un caractère | pointeur ou `NULL` |
| `strstr(s, sub)` | cherche une sous-chaîne | pointeur ou `NULL` |

- `strcmp` compare les octets comme des `unsigned char` et s'arrête à la
  première différence ; si l'une est un préfixe de l'autre, la plus courte est
  plus petite.
- `strchr(s, '\0')` renvoie un pointeur sur le terminateur : le `'\0'` fait
  partie de la chaîne. C'est `strings5` et `strings10`.

## `snprintf` : écrire sans déborder

`strcpy` et `strcat` ne connaissent pas la taille de la destination. Préfère
`snprintf`, qui prend la taille du tampon **entier** (`'\0'` compris) et tronque
proprement au lieu de déborder.

```c
int n = snprintf(dst, taille, "Bonjour %s", nom);
```

`snprintf` renvoie le nombre d'octets qu'il **aurait fallu** écrire, hors
terminateur : donc `n >= taille` signale une troncature. Avec `taille == 0`, rien
n'est écrit et le retour reste calculé.

```c
int saluer(char *dst, size_t taille, const char *nom)
{
    int n = snprintf(dst, taille, "Bonjour %s", nom);
    return n >= 0 && (size_t)n < taille;   // 1 si tout a tenu
}
```

C'est l'exercice `strings2`. `strcpy`/`strcat` restent corrects uniquement quand
l'appelant a prouvé que la destination est assez grande.

## `strlcat` et `strlcpy` (mention)

Sur BSD et macOS, `strlcat(dst, src, taille)` concatène en garantissant un `'\0'`
final et renvoie la longueur qu'aurait eue la chaîne sans troncature ; avec
`taille == 0`, elle renvoie `strlen(src)` sans lire `dst`. Ce n'est **pas** dans
la norme ISO C : pour du code portable, reste sur `snprintf`. C'est `strings6`.

## Minuscules, majuscules : attention au type

`tolower`/`toupper` attendent « un `unsigned char` converti en `int` » (ou
`EOF`). Leur passer un `char` négatif est un comportement indéfini.

```c
#include <ctype.h>
c = (char)tolower((unsigned char)c);
```

La règle vaut pour `isalpha`, `isdigit`, `isspace`, etc. C'est le point délicat
de `strings9`.

## Parcourir une chaîne

Une boucle s'arrête au `'\0'` :

```c
size_t ma_strlen(const char *s)
{
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}
```

Variante pointeur, équivalente : `while (*s) { s++; n++; }`.

## Réimplémenter `strcpy`

```c
char *ma_strcpy(char *dst, const char *src)
{
    char *retour = dst;
    while ((*dst++ = *src++) != '\0') { }
    return retour;
}
```

L'affectation copie, puis sa valeur sert de condition : le `'\0'` est copié
**et** arrête la boucle. C'est `strings3`.

## Inverser une chaîne

On échange les extrémités sans jamais toucher au `'\0'`, en s'arrêtant à `n / 2`.

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

C'est `strings8`.

## Palindrome

Deux indices qui se rapprochent ; on compare `tolower` des deux côtés pour
ignorer la casse sans casser les octets accentués.

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

Une chaîne vide ou d'un seul caractère est un palindrome. C'est `strings9`.

## Compter les mots

Un mot est une suite maximale de caractères qui ne sont pas des blancs : compter
les mots revient à compter les transitions blanc -> non-blanc.

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

C'est `strings7`.

## Le réflexe

Toute chaîne est un tableau avec un octet de plus que sa longueur. Avant
d'écrire : **le tampon a-t-il la place du `'\0'`**, **l'écriture est-elle
bornée**, **la source est-elle modifiable**. Et pour la casse, caste toujours en
`unsigned char`.

Exercices liés : `strings1`..`strings10`.
