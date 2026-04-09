#!/usr/bin/env python3
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
COEFFS = ROOT / "src" / "transform_coeffs.h"
IDCT2 = ROOT / "src" / "IDCT2.cpp"

BIT_TERMS = [
    (64, "a"),
    (32, "b"),
    (16, "c"),
    (8, "d"),
    (4, "e"),
    (2, "f"),
    (1, "g"),
]


def _extract_matrix(text: str, name: str) -> list[list[int]]:
    marker = f"const ap_int<8> {name}"
    start = text.find(marker)
    if start == -1:
        raise ValueError(f"Could not find matrix {name}")

    eq = text.find("=", start)
    if eq == -1:
        raise ValueError(f"Could not find '=' for matrix {name}")

    brace_start = text.find("{", eq)
    if brace_start == -1:
        raise ValueError(f"Could not find opening brace for matrix {name}")

    depth = 0
    i = brace_start
    while i < len(text):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                block = text[brace_start : i + 1]
                break
        i += 1
    else:
        raise ValueError(f"Could not find closing brace for matrix {name}")

    rows = []
    for row_match in re.finditer(r"\{([^{}]*)\}", block):
        nums = [int(x.strip()) for x in row_match.group(1).split(",") if x.strip()]
        rows.append(nums)

    if not rows:
        raise ValueError(f"No rows parsed for matrix {name}")
    return rows


def _extract_function(text: str, func_name: str) -> tuple[int, int, str]:
    sig = f"void {func_name}("
    start = text.find(sig)
    if start == -1:
        raise ValueError(f"Function {func_name} not found")

    open_brace = text.find("{", start)
    if open_brace == -1:
        raise ValueError(f"Could not find function body for {func_name}")

    depth = 0
    i = open_brace
    while i < len(text):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return start, i + 1, text[start : i + 1]
        i += 1

    raise ValueError(f"Could not match closing brace for {func_name}")


def _coeff_expr(row_idx: int, coeff: int) -> str:
    if coeff == 0:
        return "0"

    remaining = abs(coeff)
    terms = []
    for value, suffix in BIT_TERMS:
        if remaining >= value:
            terms.append(f"in{row_idx}_{suffix}")
            remaining -= value

    if remaining != 0:
        raise ValueError(f"Could not decompose coefficient {coeff}")

    expr = " + ".join(terms)
    if coeff < 0:
        return f"-({expr})"
    return expr


def _build_rows_block(matrix: list[list[int]], row_indices: list[int], cols: int) -> str:
    parts = []
    for row_idx in row_indices:
        arr_name = f"in{row_idx}s"
        parts.append(f"    ap_int<32> {arr_name}[{cols}];")
        parts.append(f"    #pragma HLS ARRAY_PARTITION variable={arr_name} complete dim=0")
        parts.append("")
        for col in range(cols):
            expr = _coeff_expr(row_idx, matrix[row_idx][col])
            parts.append(f"    {arr_name}[{col}] = {expr};")
        parts.append("")
    return "\n".join(parts).rstrip() + "\n"


def _replace_in_function(function_text: str, pattern: str, replacement: str) -> str:
    new_text, count = re.subn(pattern, replacement + r"\2", function_text, count=1, flags=re.DOTALL)
    if count != 1:
        raise ValueError("Could not locate replacement region inside function")
    return new_text


def main() -> None:
    coeffs_text = COEFFS.read_text()
    idct16 = _extract_matrix(coeffs_text, "idct16")
    idct32 = _extract_matrix(coeffs_text, "idct32")

    cpp_text = IDCT2.read_text()

    # IDCT2B16: regenerate odd rows 1..15 (8 outputs each)
    b16_start, b16_end, b16_text = _extract_function(cpp_text, "IDCT2B16")
    b16_rows = list(range(1, 16, 2))
    b16_block = _build_rows_block(idct16, b16_rows, 8)
    b16_text = _replace_in_function(
        b16_text,
        r"(\s*ap_int<32>\s+in1s\[8\];[\s\S]*?)(\n\s*for\(int i=0; i<\d+; i\+\+\)\{)",
        "\n" + b16_block,
    )
    b16_text = re.sub(r"\bin1\[(\d+)\]", r"in[\1]", b16_text)
    b16_text = re.sub(
        r"for\(int i=0; i<\d+; i\+\+\)\{\n\s*#pragma HLS UNROLL\n\s*odds\[i\] = in1s\[i\]",
        "for(int i=0; i<8; i++){\n        #pragma HLS UNROLL\n        odds[i] = in1s[i]",
        b16_text,
        count=1,
    )
    cpp_text = cpp_text[:b16_start] + b16_text + cpp_text[b16_end:]

    # IDCT2B32: regenerate odd rows 3..31 (16 outputs each), keep in1s as-is
    b32_start, b32_end, b32_text = _extract_function(cpp_text, "IDCT2B32")
    b32_rows = list(range(3, 32, 2))
    b32_block = _build_rows_block(idct32, b32_rows, 16)
    b32_text = _replace_in_function(
        b32_text,
        r"(\s*ap_int<32>\s+in3s\[16\];[\s\S]*?)(\n\s*for\(int i=0; i<16; i\+\+\)\{)",
        "\n" + b32_block,
    )
    cpp_text = cpp_text[:b32_start] + b32_text + cpp_text[b32_end:]

    IDCT2.write_text(cpp_text)
    print("Updated IDCT2B16 and IDCT2B32 odd-row shift-add blocks in src/IDCT2.cpp")


if __name__ == "__main__":
    main()
