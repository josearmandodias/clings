#!/usr/bin/env python3
"""Genere les cartes mentales SVG a partir des fiches markdown.

Une carte = un noeud central (le titre `#` de la fiche) et une branche par
section `##`, chacune portant ses sous-sections `###`. Les fichiers produits
sont commits dans `fiches/cartes/{fr,en}/`, donc lisibles sur GitHub sans rien
executer ; ce script sert seulement a les regenerer apres une modification.

    dev/gen-cartes.py

Necessite Python 3 (aucune dependance externe).
"""
import glob
import html
import math
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FICHES = os.path.join(ROOT, "fiches")

PALETTE = [
    "#d1495b", "#00798c", "#edae49", "#2e4057", "#6a4c93",
    "#3d9970", "#e07a5f", "#457b9d", "#8d6a9f", "#bc6c25",
    "#2a9d8f", "#c1121f", "#4361ee", "#6c757d",
]

RE_H1 = re.compile(r"^#\s+(.*)$")
RE_H2 = re.compile(r"^##\s+(.*)$")
RE_H3 = re.compile(r"^###\s+(.*)$")


def parse(path):
    """Retourne (titre, [(section, [sous-sections]), ...])."""
    title = ""
    branches = []
    current = None
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            m = RE_H1.match(line)
            if m:
                if not title:
                    title = m.group(1).strip()
                continue
            m = RE_H2.match(line)
            if m:
                current = {"t": m.group(1).strip(), "subs": []}
                branches.append(current)
                continue
            m = RE_H3.match(line)
            if m and current is not None:
                current["subs"].append(m.group(1).strip())
    return title, branches


def text_w(s, size):
    return len(s) * size * 0.58


def layout(title, branches):
    nodes = []
    edges = []
    root_w = max(150.0, text_w(title, 20) + 44)
    root_h = 54.0
    nodes.append(dict(x=0.0, y=0.0, w=root_w, h=root_h, fill="#1f2937",
                      stroke="#1f2937", text=title, size=20,
                      tc="#ffffff", bold=True))

    n = len(branches)
    max_h2 = max(text_w(b["t"], 13) for b in branches)
    all_subs = [s for b in branches for s in b["subs"]]
    max_h3 = max((text_w(s, 12) for s in all_subs), default=80.0)

    r1 = root_w / 2 + 90 + max_h2 / 2
    r2 = r1 + 120 + max_h3 / 2

    for i, branch in enumerate(branches):
        ang = -math.pi / 2 + 2 * math.pi * i / n
        x = r1 * math.cos(ang)
        y = r1 * math.sin(ang)
        color = PALETTE[i % len(PALETTE)]
        nodes.append(dict(x=x, y=y, w=max(76.0, text_w(branch["t"], 13) + 24),
                          h=30.0, fill=color, stroke=color, text=branch["t"],
                          size=13, tc="#ffffff"))
        edges.append((0.0, 0.0, x, y))

        subs = branch["subs"]
        k = len(subs)
        sector = (2 * math.pi / n) * 0.92
        for j, sub in enumerate(subs):
            off = 0.0 if k == 1 else (j - (k - 1) / 2) * (sector / max(k - 1, 1))
            a2 = ang + off
            x2 = r2 * math.cos(a2)
            y2 = r2 * math.sin(a2)
            nodes.append(dict(x=x2, y=y2, w=max(66.0, text_w(sub, 12) + 20),
                              h=26.0, fill="#ffffff", stroke=color, text=sub,
                              size=12, tc="#374151"))
            edges.append((x, y, x2, y2))
    return nodes, edges


def render(nodes, edges):
    pad = 44.0
    minx = min(nd["x"] - nd["w"] / 2 for nd in nodes) - pad
    maxx = max(nd["x"] + nd["w"] / 2 for nd in nodes) + pad
    miny = min(nd["y"] - nd["h"] / 2 for nd in nodes) - pad
    maxy = max(nd["y"] + nd["h"] / 2 for nd in nodes) + pad
    width = maxx - minx
    height = maxy - miny

    out = []
    out.append('<?xml version="1.0" encoding="UTF-8"?>')
    out.append(
        '<svg xmlns="http://www.w3.org/2000/svg" '
        f'viewBox="0 0 {width:.0f} {height:.0f}" '
        f'width="{width:.0f}" height="{height:.0f}" '
        'font-family="-apple-system,Segoe UI,Roboto,Helvetica,Arial,sans-serif">'
    )
    out.append(f'<rect x="0" y="0" width="{width:.0f}" height="{height:.0f}" fill="#ffffff"/>')

    for (x1, y1, x2, y2) in edges:
        tx1, ty1, tx2, ty2 = x1 - minx, y1 - miny, x2 - minx, y2 - miny
        cx = ((x1 + x2) / 2) * 0.90 - minx
        cy = ((y1 + y2) / 2) * 0.90 - miny
        out.append(
            f'<path d="M {tx1:.1f} {ty1:.1f} Q {cx:.1f} {cy:.1f} '
            f'{tx2:.1f} {ty2:.1f}" fill="none" stroke="#cbd5e1" stroke-width="1.5"/>'
        )

    for nd in nodes:
        x = nd["x"] - minx
        y = nd["y"] - miny
        w = nd["w"]
        h = nd["h"]
        weight = "700" if nd.get("bold") else "500"
        baseline = y + nd["size"] * 0.35
        out.append(
            f'<rect x="{x - w / 2:.1f}" y="{y - h / 2:.1f}" width="{w:.1f}" '
            f'height="{h:.1f}" rx="{h / 2:.1f}" fill="{nd["fill"]}" '
            f'stroke="{nd["stroke"]}" stroke-width="1.5"/>'
        )
        out.append(
            f'<text x="{x:.1f}" y="{baseline:.1f}" text-anchor="middle" '
            f'font-size="{nd["size"]}" font-weight="{weight}" '
            f'fill="{nd["tc"]}">{html.escape(nd["text"])}</text>'
        )

    out.append("</svg>")
    return "\n".join(out) + "\n"


def carte_name(basename):
    return basename[:-2] if basename.endswith("-c") else basename


def main():
    total = 0
    for lang in ("fr", "en"):
        srcdir = os.path.join(FICHES, lang)
        outdir = os.path.join(FICHES, "cartes", lang)
        os.makedirs(outdir, exist_ok=True)
        for path in sorted(glob.glob(os.path.join(srcdir, "*.md"))):
            base = os.path.basename(path)[:-3]
            title, branches = parse(path)
            if not branches:
                print(f"ignore (aucune section ##) : {path}", file=sys.stderr)
                continue
            title = re.sub(r"\s*[\u2014\u2013-]\s*(fiche|cheat sheet)\s*$", "", title).strip()
            nodes, edges = layout(title or carte_name(base), branches)
            svg = render(nodes, edges)
            out_path = os.path.join(outdir, carte_name(base) + ".svg")
            with open(out_path, "w", encoding="utf-8") as fh:
                fh.write(svg)
            subs = sum(len(b["subs"]) for b in branches)
            print(f"{out_path}  ({len(branches)} branches, {subs} sous-branches)")
            total += 1
    print(f"\n{total} cartes generees.")


if __name__ == "__main__":
    main()
