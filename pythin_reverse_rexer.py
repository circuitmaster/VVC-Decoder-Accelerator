import re

# =======================
# CONFIG
# =======================

PREFIX = "in31"      # variable prefix
SUFFIX = "_2"       # variable suffix
ARRAY  = "in31s_2"   # array name

# =======================
# INPUT (paste directly here)
# =======================

INPUT_LINE = """
  {  2, -7, 11, -15, 20, -24, 28, -33, 37, -41, 44, -48, 52, -56, 59, -62, 65, -69, 71, -73, 77, -79, 81, -83, 84, -86, 87, -88, 90, -90, 90, -91, 91, -90, 90, -90, 88, -87, 86, -84, 83, -81, 79, -77, 73, -71, 69, -65, 62, -59, 56, -52, 48, -44, 41, -37, 33, -28, 24, -20, 15, -11,  7, -2 }
"""

# =======================
# WEIGHTS
# =======================

WEIGHTS = [
    ('a', 64),
    ('b', 32),
    ('c', 16),
    ('d', 8),
    ('e', 4),
    ('f', 2),
    ('g', 1),
]

# =======================
# PARSE INPUT
# =======================

# extract all numbers from the curly braces
numbers = [int(x) for x in re.findall(r'-?\d+', INPUT_LINE)]

# take only first 32 entries
numbers = numbers[:32]

# =======================
# HELPER
# =======================

def build_expr(n):
    """Convert integer n to + term expression, negative wrapped with -(...)"""
    neg = n < 0
    n = abs(n)

    terms = []
    for name, value in WEIGHTS:
        if n >= value:
            n -= value
            terms.append(f"{PREFIX}_{name}{SUFFIX}")

    expr = " + ".join(terms)
    if neg:
        return f"-({expr})"
    return expr

# =======================
# OUTPUT
# =======================

for i, val in enumerate(numbers):
    rhs = build_expr(val)
    print(f"{ARRAY}[{i:<2}] =  {rhs};")
