# Les fichiers en C — fiche

En C, un fichier est un flux d'octets représenté par un `FILE *`. On l'ouvre, on
lit ou on écrit, on le ferme. Pas d'exceptions : une erreur se signale par une
**valeur de retour** et, pour l'OS, par `errno`. Cette fiche accompagne le
chapitre `08_io`.

## Ouvrir et fermer

```c
#include <stdio.h>

FILE *f = fopen("data.txt", "r");
if (f == NULL) {
    perror("fopen");       // affiche le message système
    return 1;
}
/* ... */
fclose(f);                 // toujours fermer, surtout en cas d'erreur
```

| Mode | Lecture | Écriture | Tronque | Position initiale |
|---|---|---|---|---|
| `"r"` | oui | — | — | début |
| `"w"` | — | oui | oui | début |
| `"a"` | — | oui | — | fin (ajout) |
| `"r+"` | oui | oui | — | début |
| `"w+"` | oui | oui | oui | début |
| `"a+"` | oui | oui | — | fin |

Ajoute un `b` pour le binaire (`"rb"`, `"wb"`), surtout utile sous Windows.
`fopen` renvoie `NULL` si le fichier n'existe pas (en `"r"`) ou n'est pas
accessible.

## Lire du texte avec `fgets`

`fgets(buf, taille, f)` lit au plus `taille - 1` caractères, garde le `'\n'` s'il
tient, ajoute `'\0'` et renvoie `NULL` en fin de fichier ou en cas d'erreur. Il ne
peut **pas** déborder, contrairement à `gets` (retiré du langage en 2011).

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

Un fichier vide compte 0 ligne ; une dernière ligne sans `'\n'` compte pour 1.
C'est `io1`.

## Écrire du texte

```c
fprintf(f, "%d\n", valeur);   // comme printf, vers un FILE *
fputs("texte", f);            // sans '\n' ajouté
fputc('x', f);
fflush(f);                    // force l'écriture sur le disque
```

`fprintf` renvoie un nombre négatif en cas d'erreur : vérifie-le sur les écritures
critiques. `fputs` n'ajoute pas de saut de ligne. C'est `io2`.

## Lire et écrire en binaire

```c
size_t n = fwrite(tab, sizeof *tab, nb, f);   // mémoire -> fichier
size_t m = fread(buf, sizeof *buf, nb, f);    // fichier -> mémoire
```

Les deux renvoient le **nombre d'éléments** traités : compare-le à `nb` pour
détecter un échec ou une fin de fichier. `fwrite`/`fread` ne font aucune
conversion, c'est la mémoire brute.

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

C'est `io3`.

## `fseek`, `ftell` et la taille d'un fichier

`fseek` déplace le curseur, `ftell` donne sa position en octets.

```c
fseek(f, 0, SEEK_END);   // aller à la fin
long taille = ftell(f);  // nombre d'octets
rewind(f);               // retour au début : fseek(f, 0, SEEK_SET)
```

`ftell` peut échouer (`-1`) : vérifie la valeur avant de t'en servir. C'est
`errors2`.

## Fin de fichier et erreurs

- `fgets` renvoie `NULL` en fin de fichier **ou** sur erreur ; distingue avec
  `feof(f)` et `ferror(f)`.
- `getchar()` renvoie `EOF` (une valeur négative, pas un `char`) à la fin ;
  compare toujours à un `int`, jamais à un `char`.
- Après une erreur d'écriture, pense tout de même à `fclose`.

## Gestion d'erreur à la C

Pas d'exception : la convention est « valeur de retour = statut », et `errno`
(dans `<errno.h>`) dit pourquoi l'appel système a échoué.

```c
#include <errno.h>

errno = 0;
FILE *f = fopen("/aucun/fichier", "r");
if (f == NULL) {
    perror("fopen");                          // "fopen: No such file or directory"
    fprintf(stderr, "%s\n", strerror(errno)); // le message seul
}
```

- on ne lit `errno` **que** si l'appel a signalé une erreur ;
- on remet `errno = 0` avant un appel qui peut renvoyer une valeur légitime
  indistinguable d'une erreur ;
- `perror` ajoute le message système, `strerror(errno)` le donne seul.

## `strtol` : convertir avec contrôle

`atoi` ne signale rien. `strtol` est la version sûre :

```c
#include <stdlib.h>
#include <errno.h>

errno = 0;
char *fin;
long v = strtol(s, &fin, 10);   // base 10

if (fin == s) {
    /* aucun chiffre lu : entrée invalide */
} else if (*fin != '\0') {
    /* caractères parasites après le nombre */
} else if (errno == ERANGE) {
    /* dépassement de la plage d'un long */
}
/* ici : succès, v est valide */
```

`strtol` saute les blancs, accepte un `+`/`-`, lit les chiffres, puis pose `fin`
sur le premier caractère **non consommé**. Si aucun chiffre n'est lu, `fin` reste
égal à `s`. `ERANGE` (dans `<errno.h>`) signale le dépassement. C'est `errors1`
et `errors3`.

## Le réflexe

Chaque `fopen` a son `fclose`, chaque lecture teste sa valeur de retour, et
`errno` ne se lit qu'après un échec **signalé**. Pour convertir du texte en
nombre : `strtol` avec `endptr` et `ERANGE`, jamais `atoi`.

Exercices liés : `io1`..`io3`, `errors1`..`errors3`.
