import re

# =======================
# CONFIG / INPUT SECTION
# =======================

INPUT_TEXT = """
    in1s_2[0]  =  in1_a_2 - in1_f_2;
    in1s_2[1]  = -(in1_a_2 + in1_e_2 + in1_g_2);
    in1s_2[2]  = -(in1_b_2 + in1_c_2 + in1_d_2);
    in1s_2[3]  =  in1_a_2 + in1_d_2 + in1_g_2;
    in1s_2[4]  =  in1_b_2 + in1_c_2;
    in1s_2[5]  = -(in1_a_2 + in1_d_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[6]  = -(in1_b_2 + in1_d_2 + in1_g_2);
    in1s_2[7]  =  in1_a_2 + in1_c_2 + in1_f_2 + in1_g_2;
    in1s_2[8]  =  in1_b_2 + in1_g_2;
    in1s_2[9]  = -(in1_a_2 + in1_c_2 + in1_e_2 + in1_f_2);
    in1s_2[10] = -(in1_c_2 + in1_d_2);
    in1s_2[11] =  in1_a_2 + in1_c_2 + in1_d_2;
    in1s_2[12] =  in1_d_2 + in1_e_2 + in1_f_2 + in1_g_2;
    in1s_2[13] = -(in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2);
    in1s_2[14] = -(in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[15] =  in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[16] = -in1_f_2;
    in1s_2[17] = -(in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2);
    in1s_2[18] =  in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[19] =  in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2;
    in1s_2[20] = -(in1_c_2 + in1_e_2);
    in1s_2[21] = -(in1_a_2 + in1_c_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[22] =  in1_c_2 + in1_d_2 + in1_e_2;
    in1s_2[23] =  in1_a_2 + in1_c_2 + in1_e_2;
    in1s_2[24] = -(in1_b_2 + in1_e_2 + in1_g_2);
    in1s_2[25] = -(in1_a_2 + in1_c_2 + in1_g_2);
    in1s_2[26] =  in1_b_2 + in1_d_2 + in1_e_2;
    in1s_2[27] =  in1_a_2 + in1_d_2 + in1_e_2 + in1_g_2;
    in1s_2[28] = -(in1_b_2 + in1_c_2 + in1_e_2);
    in1s_2[29] = -(in1_a_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[30] =  in1_b_2 + in1_c_2 + in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[31] =  in1_a_2 + in1_g_2;



"""

# =======================
# LOGIC SECTION
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

line_re = re.compile(
    r"""
    =\s*
    (?P<neg>-\()?
    (?P<body>[^);]+)
    \)?
    \s*;
    """,
    re.VERBOSE
)

term_re = re.compile(r'_([a-g])\b')

results = []

for line in INPUT_TEXT.splitlines():
    match = line_re.search(line)
    if not match:
        continue

    negated = match.group('neg') is not None
    body = match.group('body')

    value = sum(WEIGHTS[t] for t in term_re.findall(body))
    results.append(-value if negated else value)

# =======================
# OUTPUT SECTION
# =======================

print("Output values:")
print(", ".join(map(str, results)))
