import re

def call_blabla(matrix, values, order_input, size):
    """
    Fully supports multi-character symbols (e.g., a, aa, ab, abc)
    
    Parameters:
        matrix: string, C-style symbolic NxN matrix
        values: tuple/list of numbers
        order_input: string, e.g., "(a,aa,ab,abc)"
        size: int, NxN matrix size
    Returns:
        string: expanded numeric matrix in C-style formatting
    """

    # -----------------------------------------
    # Parse order_input to extract symbols
    # -----------------------------------------
    # Matches multi-character symbols separated by commas
    order_symbols = re.findall(r"[A-Za-z]+", order_input)
    
    if len(order_symbols) != len(values):
        raise ValueError(
            f"Number of symbols ({len(order_symbols)}) does not match number of values ({len(values)})"
        )

    # Build symbol -> value mapping
    symbol_to_value = dict(zip(order_symbols, values))

    # -----------------------------------------
    # Replacement function for regex
    # -----------------------------------------
    # Matches optional negative sign + multi-character symbol
    def replace_symbol(match):
        token = match.group(0)
        if token.startswith('-'):
            sym = token[1:]
            if sym not in symbol_to_value:
                raise ValueError(f"Symbol '{sym}' not found in order_input")
            return str(-symbol_to_value[sym])
        else:
            sym = token
            if sym not in symbol_to_value:
                raise ValueError(f"Symbol '{sym}' not found in order_input")
            return str(symbol_to_value[sym])

    expanded_raw = re.sub(r"-?[A-Za-z]+", replace_symbol, matrix)

    # -----------------------------------------
    # Extract rows
    # -----------------------------------------
    row_contents = re.findall(r"{([^{}]+)}", expanded_raw)
    if len(row_contents) != size:
        raise ValueError(f"Matrix row count {len(row_contents)} does not match expected size {size}")

    numeric_rows = []
    for r in row_contents:
        nums = [int(x) for x in re.findall(r"-?\d+", r)]
        if len(nums) != size:
            raise ValueError("Matrix column count mismatch")
        numeric_rows.append(nums)

    # -----------------------------------------
    # Format output in clean C-style
    # -----------------------------------------
    formatted_rows = []
    for row in numeric_rows:
        line = ", ".join(f"{v:2d}" for v in row)
        formatted_rows.append(f"  {{ {line} }}")

    result = "{\n" + ",\n".join(formatted_rows) + "\n};"
    return result


# -------------------------------
# EXAMPLE USAGE
# -------------------------------

matrix = r"""
{ \
  {  a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,  p,  q,  r,  s,  t,  u,  v,  w,  x,  y,  z,  A,  B,  C,  D,  E,  F,}, \
  {  c,  f,  i,  l,  o,  r,  u,  x,  A,  D,  F,  C,  z,  w,  t,  q,  n,  k,  h,  e,  b, -a, -d, -g, -j, -m, -p, -s, -v, -y, -B, -E,}, \
  {  e,  j,  o,  t,  y,  D,  D,  y,  t,  o,  j,  e,  0, -e, -j, -o, -t, -y, -D, -D, -y, -t, -o, -j, -e,  0,  e,  j,  o,  t,  y,  D,}, \
  {  g,  n,  u,  B,  D,  w,  p,  i,  b, -e, -l, -s, -z, -F, -y, -r, -k, -d,  c,  j,  q,  x,  E,  A,  t,  m,  f, -a, -h, -o, -v, -C,}, \
  {  i,  r,  A,  C,  t,  k,  b, -g, -p, -y, -E, -v, -m, -d,  e,  n,  w,  F,  x,  o,  f, -c, -l, -u, -D, -z, -q, -h,  a,  j,  s,  B,}, \
  {  k,  v,  F,  u,  j, -a, -l, -w, -E, -t, -i,  b,  m,  x,  D,  s,  h, -c, -n, -y, -C, -r, -g,  d,  o,  z,  B,  q,  f, -e, -p, -A,}, \
  {  m,  z,  z,  m,  0, -m, -z, -z, -m,  0,  m,  z,  z,  m,  0, -m, -z, -z, -m,  0,  m,  z,  z,  m,  0, -m, -z, -z, -m,  0,  m,  z,}, \
  {  o,  D,  t,  e, -j, -y, -y, -j,  e,  t,  D,  o,  0, -o, -D, -t, -e,  j,  y,  y,  j, -e, -t, -D, -o,  0,  o,  D,  t,  e, -j, -y,}, \
  {  q,  E,  n, -c, -t, -B, -k,  f,  w,  y,  h, -i, -z, -v, -e,  l,  C,  s,  b, -o, -F, -p,  a,  r,  D,  m, -d, -u, -A, -j,  g,  x,}, \
  {  s,  A,  h, -k, -D, -p,  c,  v,  x,  e, -n, -F, -m,  f,  y,  u,  b, -q, -C, -j,  i,  B,  r, -a, -t, -z, -g,  l,  E,  o, -d, -w,}, \
  {  u,  w,  b, -s, -y, -d,  q,  A,  f, -o, -C, -h,  m,  E,  j, -k, -F, -l,  i,  D,  n, -g, -B, -p,  e,  z,  r, -c, -x, -t,  a,  v,}, \
  {  w,  s, -d, -A, -o,  h,  E,  k, -l, -D, -g,  p,  z,  c, -t, -v,  a,  x,  r, -e, -B, -n,  i,  F,  j, -m, -C, -f,  q,  y,  b, -u,}, \
  {  y,  o, -j, -D, -e,  t,  t, -e, -D, -j,  o,  y,  0, -y, -o,  j,  D,  e, -t, -t,  e,  D,  j, -o, -y,  0,  y,  o, -j, -D, -e,  t,}, \
  {  A,  k, -p, -v,  e,  F,  f, -u, -q,  j,  B,  a, -z, -l,  o,  w, -d, -E, -g,  t,  r, -i, -C, -b,  y,  m, -n, -x,  c,  D,  h, -s,}, \
  {  C,  g, -v, -n,  o,  u, -h, -B,  a,  D,  f, -w, -m,  p,  t, -i, -A,  b,  E,  e, -x, -l,  q,  s, -j, -z,  c,  F,  d, -y, -k,  r,}, \
  {  E,  c, -B, -f,  y,  i, -v, -l,  s,  o, -p, -r,  m,  u, -j, -x,  g,  A, -d, -D,  a,  F,  b, -C, -e,  z,  h, -w, -k,  t,  n, -q,}, \
  {  F, -a, -E,  b,  D, -c, -C,  d,  B, -e, -A,  f,  z, -g, -y,  h,  x, -i, -w,  j,  v, -k, -u,  l,  t, -m, -s,  n,  r, -o, -q,  p,}, \
  {  D, -e, -y,  j,  t, -o, -o,  t,  j, -y, -e,  D,  0, -D,  e,  y, -j, -t,  o,  o, -t, -j,  y,  e, -D,  0,  D, -e, -y,  j,  t, -o,}, \
  {  B, -i, -s,  r,  j, -A, -a,  C, -h, -t,  q,  k, -z, -b,  D, -g, -u,  p,  l, -y, -c,  E, -f, -v,  o,  m, -x, -d,  F, -e, -w,  n,}, \
  {  z, -m, -m,  z,  0, -z,  m,  m, -z,  0,  z, -m, -m,  z,  0, -z,  m,  m, -z,  0,  z, -m, -m,  z,  0, -z,  m,  m, -z,  0,  z, -m,}, \
  {  x, -q, -g,  E, -j, -n,  A, -c, -u,  t,  d, -B,  m,  k, -D,  f,  r, -w, -a,  y, -p, -h,  F, -i, -o,  z, -b, -v,  s,  e, -C,  l,}, \
  {  v, -u, -a,  w, -t, -b,  x, -s, -c,  y, -r, -d,  z, -q, -e,  A, -p, -f,  B, -o, -g,  C, -n, -h,  D, -m, -i,  E, -l, -j,  F, -k,}, \
  {  t, -y,  e,  o, -D,  j,  j, -D,  o,  e, -y,  t,  0, -t,  y, -e, -o,  D, -j, -j,  D, -o, -e,  y, -t,  0,  t, -y,  e,  o, -D,  j,}, \
  {  r, -C,  k,  g, -y,  v, -d, -n,  F, -o, -c,  u, -z,  h,  j, -B,  s, -a, -q,  D, -l, -f,  x, -w,  e,  m, -E,  p,  b, -t,  A, -i,}, \
  {  p, -F,  q, -a, -o,  E, -r,  b,  n, -D,  s, -c, -m,  C, -t,  d,  l, -B,  u, -e, -k,  A, -v,  f,  j, -z,  w, -g, -i,  y, -x,  h,}, \
  {  n, -B,  w, -i, -e,  s, -F,  r, -d, -j,  x, -A,  m,  a, -o,  C, -v,  h,  f, -t,  E, -q,  c,  k, -y,  z, -l, -b,  p, -D,  u, -g,}, \
  {  l, -x,  C, -q,  e,  g, -s,  E, -v,  j,  b, -n,  z, -A,  o, -c, -i,  u, -F,  t, -h, -d,  p, -B,  y, -m,  a,  k, -w,  D, -r,  f,}, \
  {  j, -t,  D, -y,  o, -e, -e,  o, -y,  D, -t,  j,  0, -j,  t, -D,  y, -o,  e,  e, -o,  y, -D,  t, -j,  0,  j, -t,  D, -y,  o, -e,}, \
  {  h, -p,  x, -F,  y, -q,  i, -a, -g,  o, -w,  E, -z,  r, -j,  b,  f, -n,  v, -D,  A, -s,  k, -c, -e,  m, -u,  C, -B,  t, -l,  d,}, \
  {  f, -l,  r, -x,  D, -C,  w, -q,  k, -e, -a,  g, -m,  s, -y,  E, -B,  v, -p,  j, -d, -b,  h, -n,  t, -z,  F, -A,  u, -o,  i, -c,}, \
  {  d, -h,  l, -p,  t, -x,  B, -F,  C, -y,  u, -q,  m, -i,  e, -a, -c,  g, -k,  o, -s,  w, -A,  E, -D,  z, -v,  r, -n,  j, -f,  b,}, \
  {  b, -d,  f, -h,  j, -l,  n, -p,  r, -t,  v, -x,  z, -B,  D, -F,  E, -C,  A, -y,  w, -u,  s, -q,  o, -m,  k, -i,  g, -e,  c, -a,}, \
}







"""

values = (4,     9,    13,    17,    21,    26,    30,    34,    38,    42,    46,    50,    53,    56,    60,    63,    66,    68,    72,    74,    77,    78,    80,    82,    84,    85,    86,    87,    88,    89,    90,    90)
order_input = "(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,A,B,C,D,E,F)"   # <-- now parsed automatically
size   = 32

result = call_blabla(matrix=matrix, values=values, order_input=order_input, size=size)
print(result)
