import sys
from collections import Counter
from itertools import groupby

def min_compressed_len(line: str) -> int:
    if not line: return 0

    #run-length encoding
    tokens = [f"{char}{sum(1 for _ in group)}" for char, group in groupby(line)]
    counts = Counter(tokens)

    # no tokens are replaced
    base_len = sum(len(t) * c for t, c in counts.items())

    savings = []
    for t, c in counts.items(): # for every token
        s = (c - 1) * len(t) - c
        if s > 0:
            savings.append(s)

    # Sort to pick the most profitable tokens first
    savings.sort(reverse=True)

    # header requires ';;' (overhead of 2).
    top_26_savings = sum(savings[:26])
    if top_26_savings > 2: return base_len - (top_26_savings - 2)
    
    return base_len

def solve(filename="input.txt"):
    with open(filename, "r") as f:
        lines = f.read().splitlines()

    total = sum(min_compressed_len(line) * (idx + 1) for idx, line in enumerate(lines))
    print(total)

if __name__ == "__main__":
    solve()
