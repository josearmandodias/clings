# Les bits en C — fiche

Manipuler les bits revient partout : drapeaux, protocoles, hachage, codes
d'erreur, compression. C'est aussi l'endroit où l'on rencontre le plus de
comportements indéfinis si l'on ne fait pas attention. Cette fiche accompagne
le chapitre `11_bitwise`.

## Représentation des entiers

Un `unsigned int` de 32 bits code les valeurs de `0` à `2^32 - 1`. Un `int`
signé utilise le complément à deux : le bit de poids fort porte le signe.

```c
0b1011        // 11  (préfixe binaire accepté par clang et gcc)
0x2A          // 42
1u << 3       // 8   : le suffixe u évite les surprises du type signé
```

Utilise **`unsigned`** dès que tu joues avec des bits. Sur un signé, `<<` peut
déborder ou décaler un négatif : comportement indéfini.

## Opérateurs

| Opérateur | Nom | Exemple | Résultat |
|---|---|---|---|
| `&` | ET bit à bit | `0b1100 & 0b1010` | `0b1000` |
| `\|` | OU bit à bit | `0b1100 \| 0b1010` | `0b1110` |
| `^` | OU exclusif | `0b1100 ^ 0b1010` | `0b0110` |
| `~` | NON bit à bit | `~0u` | tous les bits à 1 |
| `<<` | décalage à gauche | `1u << 4` | 16 |
| `>>` | décalage à droite | `16u >> 2` | 4 |

## Décalages

```c
x << n   // multiplie par 2^n (s'il n'y a pas de débordement)
x >> n   // divise par 2^n ; sur un unsigned, remplit avec des 0
```

Interdits (comportement indéfini) :

- décaler de `n >= largeur du type` : `1u << 32` sur 32 bits ;
- décaler à gauche un nombre négatif, ou dont le résultat déborde ;
- décaler à droite un nombre négatif (en pratique : dépend de
  l'implémentation).

## Manipuler un bit

```c
unsigned set_bit(unsigned x, int pos)    { return x |  (1u << pos); }
unsigned clear_bit(unsigned x, int pos)  { return x & ~(1u << pos); }
unsigned toggle_bit(unsigned x, int pos) { return x ^  (1u << pos); }
int      test_bit(unsigned x, int pos)   { return (x >> pos) & 1u; }
```

## Compter les bits à 1 (popcount)

```c
int compte_bits(unsigned x)
{
    int n = 0;
    while (x) {
        x &= x - 1;   // efface le bit à 1 le plus bas
        n++;
    }
    return n;
}
```

`x & (x - 1)` retire le bit à 1 le plus bas : la boucle ne tourne qu'autant de
fois qu'il y a de bits à 1 (et pas 32 fois).

## Masques et drapeaux

Un entier dont chaque bit est une option :

```c
#define LIRE   1u
#define ECRIRE 2u
#define EXEC   4u

unsigned perms = LIRE | ECRIRE;
(perms & ECRIRE) != 0;       // tester
perms |=  EXEC;              // ajouter
perms &= ~LIRE;              // retirer
perms ^=  ECRIRE;            // basculer
```

## Extraire un champ

Pour lire `largeur` bits à partir de `offset` :

```c
unsigned extraire(unsigned v, int offset, int largeur)
{
    unsigned masque = (1u << largeur) - 1u;   // valable si largeur < 32
    return (v >> offset) & masque;
}
```

Piège quand `largeur == 32` : `1u << 32` est indéfini. Traite ce cas à part
avec `masque = ~0u`.

## Afficher en binaire ou en hexadécimal

```c
void binaire(unsigned x, char *out)   // 32 caractères + '\0'
{
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((x >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

printf("%08X\n", 0xDEADBEEFu);   // DEADBEEF
printf("%u\n",   0b1011u);       // 11
```

## Boutisme (endianness)

En mémoire, l'octet de poids fort peut être rangé en premier (big-endian) ou
en dernier (little-endian). Inverser les octets d'un `unsigned` de 32 bits :

```c
unsigned swap32(unsigned x)
{
    return (x >> 24)
         | ((x >> 8)  & 0x0000FF00u)
         | ((x << 8)  & 0x00FF0000u)
         | (x << 24);
}
```

`swap32(0x11223344u) == 0x44332211u`.

## Champs de bits (mention)

```c
struct Drapeaux {
    unsigned lire   : 1;
    unsigned ecrire : 1;
    unsigned niveau : 3;   // 3 bits
};
```

Pratique, mais l'ordre et le remplissage des bits dépendent de
l'implémentation. À éviter pour un format binaire échangé entre machines.

## Pièges

- **Précédence** : `x & 1 == 0` se lit `x & (1 == 0)`. Parenthèse tout :
  `(x & 1) == 0`.
- `~0` est un `int` valant -1 ; écris `~0u` pour « tous les bits à 1 ».
- `1 << 31` déborde un `int` signé ; écris `1u << 31`.
- Décaler de la largeur du type (ou plus) est indéfini.
- `>>` sur un signé négatif n'est pas portable.
- Ne confonds pas `&` (ET bit à bit) et `&&` (ET logique), ni `|` et `||`.

## Compiler

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```
