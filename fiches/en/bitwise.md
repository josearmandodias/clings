# Bits in C — cheat sheet

Manipulating bits comes up everywhere: flags, protocols, hashing, error
codes, compression. It is also where you run into the most undefined
behaviour if you are not careful. This cheat sheet accompanies
the `11_bitwise` chapter.

## Integer representation

A 32-bit `unsigned int` encodes the values from `0` to `2^32 - 1`. A signed
`int` uses two's complement: the most significant bit carries the sign.

```c
0b1011        // 11  (binary prefix accepted by clang and gcc)
0x2A          // 42
1u << 3       // 8   : the u suffix avoids signed-type surprises
```

Use **`unsigned`** as soon as you play with bits. On a signed value, `<<` can
overflow or shift a negative: undefined behaviour.

## Operators

| Operator | Name | Example | Result |
|---|---|---|---|
| `&` | bitwise AND | `0b1100 & 0b1010` | `0b1000` |
| `\|` | bitwise OR | `0b1100 \| 0b1010` | `0b1110` |
| `^` | exclusive OR | `0b1100 ^ 0b1010` | `0b0110` |
| `~` | bitwise NOT | `~0u` | all bits set to 1 |
| `<<` | left shift | `1u << 4` | 16 |
| `>>` | right shift | `16u >> 2` | 4 |

## Shifts

```c
x << n   // multiplies by 2^n (if there is no overflow)
x >> n   // divides by 2^n; on an unsigned, fills with 0
```

Forbidden (undefined behaviour):

- shifting by `n >= width of the type`: `1u << 32` on 32 bits;
- left-shifting a negative number, or one whose result overflows;
- right-shifting a negative number (in practice: depends on
  the implementation).

## Manipulating a bit

```c
unsigned set_bit(unsigned x, int pos)    { return x |  (1u << pos); }
unsigned clear_bit(unsigned x, int pos)  { return x & ~(1u << pos); }
unsigned toggle_bit(unsigned x, int pos) { return x ^  (1u << pos); }
int      test_bit(unsigned x, int pos)   { return (x >> pos) & 1u; }
```

## Counting set bits (popcount)

```c
int compte_bits(unsigned x)
{
    int n = 0;
    while (x) {
        x &= x - 1;   // clears the lowest set bit
        n++;
    }
    return n;
}
```

`x & (x - 1)` removes the lowest set bit: the loop runs only as many
times as there are set bits (and not 32 times).

## Masks and flags

An integer where each bit is an option:

```c
#define LIRE   1u
#define ECRIRE 2u
#define EXEC   4u

unsigned perms = LIRE | ECRIRE;
(perms & ECRIRE) != 0;       // test
perms |=  EXEC;              // add
perms &= ~LIRE;              // remove
perms ^=  ECRIRE;            // toggle
```

## Extracting a field

To read `largeur` bits starting at `offset`:

```c
unsigned extraire(unsigned v, int offset, int largeur)
{
    unsigned masque = (1u << largeur) - 1u;   // valid if largeur < 32
    return (v >> offset) & masque;
}
```

Trap when `largeur == 32`: `1u << 32` is undefined. Handle that case separately
with `masque = ~0u`.

## Printing in binary or hexadecimal

```c
void binaire(unsigned x, char *out)   // 32 characters + '\0'
{
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((x >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

printf("%08X\n", 0xDEADBEEFu);   // DEADBEEF
printf("%u\n",   0b1011u);       // 11
```

## Endianness

In memory, the most significant byte can be stored first (big-endian) or
last (little-endian). Reversing the bytes of a 32-bit `unsigned`:

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

## Bit fields (mention)

```c
struct Drapeaux {
    unsigned lire   : 1;
    unsigned ecrire : 1;
    unsigned niveau : 3;   // 3 bits
};
```

Practical, but the order and the padding of the bits depend on
the implementation. Avoid it for a binary format exchanged between machines.

## Traps

- **Precedence**: `x & 1 == 0` reads as `x & (1 == 0)`. Parenthesize everything:
  `(x & 1) == 0`.
- `~0` is an `int` equal to -1; write `~0u` for "all bits set to 1".
- `1 << 31` overflows a signed `int`; write `1u << 31`.
- Shifting by the width of the type (or more) is undefined.
- `>>` on a negative signed value is not portable.
- Do not confuse `&` (bitwise AND) and `&&` (logical AND), nor `|` and `||`.

## Compiling

```sh
cc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined prog.c -o prog
```
