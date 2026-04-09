import re

# =======================
# INPUT
# =======================

INPUT_TEXT = """
in7s_2[0]  =  in7_b_2 + in7_c_2 + in7_e_2;
    in7s_2[1]  = -(in7_a_2 + in7_c_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[2]  =  in7_e_2 + in7_f_2 + in7_g_2;
    in7s_2[3]  =  in7_a_2 + in7_c_2 + in7_f_2 + in7_g_2;
    in7s_2[4]  = -(in7_a_2 - in7_f_2);
    in7s_2[5]  = -(in7_b_2 + in7_d_2 + in7_g_2);
    in7s_2[6]  =  in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2;
    in7s_2[7]  = -(in7_c_2 + in7_e_2);
    in7s_2[8]  = -(in7_a_2 + in7_d_2 + in7_e_2 + in7_g_2);
    in7s_2[9]  =  in7_a_2 + in7_e_2 + in7_f_2 + in7_g_2;
    in7s_2[10] =  in7_c_2 + in7_d_2 + in7_e_2;
    in7s_2[11] = -(in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2 + in7_g_2);
    in7s_2[12] =  in7_b_2 + in7_g_2;
    in7s_2[13] =  in7_a_2 + in7_c_2 + in7_c_2;
    in7s_2[14] = -(in7_a_2 + in7_d_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[15] = -(in7_d_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[16] =  in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2;
    in7s_2[17] = -(in7_b_2 + in7_d_2 + in7_e_2);
    in7s_2[18] = -(in7_b_2 + in7_c_2 + in7_d_2 + in7_f_2 + in7_g_2);
    in7s_2[19] =  in7_a_2 + in7_c_2 + in7_e_2;
    in7s_2[20] =  in7_f_2;
    in7s_2[21] = -(in7_a_2 + in7_c_2 + in7_e_2 + in7_f_2);
    in7s_2[22] =  in7_b_2 + in7_c_2 + in7_d_2;
    in7s_2[23] =  in7_b_2 + in7_c_2;
    in7s_2[24] = -(in7_a_2 + in7_c_2 + in7_d_2);
    in7s_2[25] =  in7_d_2 + in7_f_2 + in7_g_2;
    in7s_2[26] =  in7_a_2 + in7_c_2 + in7_g_2;
    in7s_2[27] = -(in7_a_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[28] = -(in7_b_2 + in7_e_2 + in7_g_2);
    in7s_2[29] =  in7_a_2 + in7_d_2 + in7_f_2;
    in7s_2[30] = -(in7_c_2 + in7_d_2);
    in7s_2[31] = -(in7_a_2 + in7_d_2 + in7_g_2);
"""

# =======================
# CONFIG
# =======================

WEIGHTS = {
    'a': 64,
    'b': 32,
    'c': 16,
    'd': 8,
    'e': 4,
    'f': 2,
    'g': 1,
}

# matches RHS, detects outer -( ... )
line_re = re.compile(
    r"""
    =\s*
    (?P<outer_neg>-\()?
    (?P<body>[^);]+)
    \)?
    \s*;
    """,
    re.VERBOSE
)

# matches signed terms: +in1_a_2, - in1_f_2, in1_c_2
term_re = re.compile(
    r"""
    (?P<sign>[+-]?)\s*
    \w+_([a-g])_\d+
    """,
    re.VERBOSE
)

# =======================
# EVALUATION
# =======================

results = []

for line in INPUT_TEXT.splitlines():
    m = line_re.search(line)
    if not m:
        continue

    outer_neg = m.group('outer_neg') is not None
    body = m.group('body')

    total = 0
    for sign, letter in term_re.findall(body):
        s = -1 if sign == '-' else 1
        total += s * WEIGHTS[letter]

    if outer_neg:
        total = -total

    results.append(total)

# =======================
# OUTPUT
# =======================

print("Output values:")
print(", ".join(map(str, results)))
