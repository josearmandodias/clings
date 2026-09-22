#!/usr/bin/env bash
# dev/check.sh — verifie l'integrite du cours clings.
#
# Pour chaque exercice de exercises/order.txt, on verifie que :
#   - l'enonce (exercises/), l'indice (hints/), la solution (solutions/) et la
#     copie vierge (.templates/) existent ;
#   - la SOLUTION compile et passe (avec ASan/UBSan si dispo) ;
#   - l'ENONCE, une fois le marqueur "I AM NOT DONE" retire, NE passe PAS
#     (sinon l'exercice est deja resolu et ne vaut rien) ;
#   - .templates/ est identique a l'enonce (utile avant de distribuer).
#
# Usage : dev/check.sh [nom ...]
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
EXDIR="$ROOT/exercises"
SOL="$ROOT/solutions"
TPL="$ROOT/.templates"
HINTS="$ROOT/hints"
ORDER="$EXDIR/order.txt"

CC_BIN="${CC:-cc}"
BASE="-std=c17 -Wall -Wextra -Werror -Wshadow -g -I$ROOT/include"

if [ -t 1 ]; then R=$'\033[31m'; G=$'\033[32m'; Y=$'\033[33m'; DIM=$'\033[2m'; N=$'\033[0m';
else R=""; G=""; Y=""; DIM=""; N=""; fi

# exercices qui fonctionnent deja par construction (on ne teste pas l'echec)
WORKING_OPTIONAL="intro1"

probe="$(mktemp)"; printf 'int main(void){return 0;}\n' > "$probe"
if $CC_BIN -fsanitize=address,undefined "$probe" -o "$probe.bin" 2>/dev/null; then
    SAN="-fsanitize=address,undefined -fno-omit-frame-pointer"
else
    SAN=""
fi
rm -f "$probe" "$probe.bin"

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

names() { grep -v '^[[:space:]]*$' "$ORDER" | grep -v '^#'; }

# compile <sortie> <main> <incdirs> <deps...> ; 0 = ok
compile() {
    local out="$1" main="$2" incs="$3"; shift 3
    # shellcheck disable=SC2086
    $CC_BIN $BASE $SAN $incs "$main" "$@" -o "$out" 2>"$out.log"
}

# run <binaire> : 0 = ok (ASAN detect_leaks desactive, comme le harnais clings)
run() { ( ASAN_OPTIONS=detect_leaks=0 "$1" >"$1.run" 2>&1 ) 2>/dev/null; }

deps_of() { # <dir> <name>
    local d deps=""
    for d in "$1/${2}_"*.c; do [ -f "$d" ] && deps="$deps $d"; done
    printf '%s' "$deps"
}

only_one=1
selected=""
for a in "$@"; do selected="$selected $a"; done

fail=0; count=0; ok=0
for rel in $(names); do
    name="$(basename "$rel" .c)"
    if [ -n "$selected" ]; then case " $selected " in *" $name "*) ;; *) continue ;; esac; fi
    count=$((count + 1))
    ex="$EXDIR/$rel"; secdir="$(dirname "$rel")"
    problems=""
    [ -f "$ex" ]            || problems="$problems enonce-manquant"
    [ -f "$SOL/$name.c" ]   || problems="$problems solution-manquante"
    [ -f "$TPL/$rel" ]      || problems="$problems template-manquant"
    [ -f "$HINTS/$name.txt" ] || problems="$problems indice-manquant"
    if [ -n "$problems" ]; then
        printf '  %sX%s %-16s%s\n' "$R" "$N" "$name" "$problems"; fail=1; continue
    fi
    if grep -q 'I AM NOT DONE' "$SOL/$name.c"; then
        printf '  %sX%s %-16s la solution contient le marqueur\n' "$R" "$N" "$name"; fail=1; continue
    fi
    if ! cmp -s "$ex" "$TPL/$rel"; then
        printf '  %sX%s %-16s template different de l enonce\n' "$R" "$N" "$name"; fail=1; continue
    fi

    # --- la solution doit passer ---
    incs="-I$ROOT/include -I$SOL -I$EXDIR/$secdir"
    sdeps="$(deps_of "$SOL" "$name")"
    [ -n "$sdeps" ] || sdeps="$(deps_of "$EXDIR/$secdir" "$name")"
    # shellcheck disable=SC2086
    if compile "$TMP/sol" "$SOL/$name.c" "$incs" $sdeps && run "$TMP/sol"; then :; else
        printf '  %sX%s %-16s LA SOLUTION ECHOUE\n' "$R" "$N" "$name"
        sed 's/^/       /' "$TMP/sol.log" 2>/dev/null | head -20
        sed 's/^/       /' "$TMP/sol.run" 2>/dev/null | head -20
        fail=1; continue
    fi

    # --- l'enonce (marqueur retire) doit echouer ---
    if [ "$name" != "$WORKING_OPTIONAL" ]; then
        sed '/I AM NOT DONE/d' "$ex" > "$TMP/eno_$name.c"
        incs="-I$ROOT/include -I$EXDIR/$secdir"
        edeps="$(deps_of "$EXDIR/$secdir" "$name")"
        if compile "$TMP/eno" "$TMP/eno_$name.c" "$incs" $edeps && run "$TMP/eno"; then
            printf '  %s!%s %-16s l enonce passe deja (trop facile ?)\n' "$Y" "$N" "$name"
            fail=1; continue
        fi
    fi

    printf '  %sv%s %-16s%s\n' "$G" "$N" "$name" "$DIM$rel$N"
    ok=$((ok + 1))
done

printf '\n  %d/%d exercices valides\n' "$ok" "$count"
exit $fail
