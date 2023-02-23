#!/usr/bin/env python3
XOR = """
#define XOR_DSZ64_IMM(dst, src, imm) \\
    CRC_UOP( _XOR_DSZ64 | DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )
#define XOR_DSZ32_IMM(dst, src, imm) \\
    CRC_UOP( _XOR_DSZ32 | DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )
#define XOR_DSZ16_IMM(dst, src, imm) \\
    CRC_UOP( _XOR_DSZ16 | DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )
#define XOR_DSZ8_IMM(dst, src, imm) \\
    CRC_UOP( _XOR_DSZ8 | DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )

#define XOR_DSZ64_REG(dst, src0, src1) \\
    CRC_UOP( _XOR_DSZ64 | DST_ENCODE(dst) | SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
#define XOR_DSZ32_REG(dst, src0, src1) \\
    CRC_UOP( _XOR_DSZ32 | DST_ENCODE(dst) | SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
#define XOR_DSZ16_REG(dst, src0, src1) \\
    CRC_UOP( _XOR_DSZ16 | DST_ENCODE(dst) | SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
#define XOR_DSZ8_REG(dst, src0, src1) \\
    CRC_UOP( _XOR_DSZ8 | DST_ENCODE(dst) | SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
"""

ops = ["ADD", "OR", "AND", "SUB", "XOR", "NOTAND", "ROL", "ROR", "RAS", "SHL", "SHR"]

for x in ops:
    print(XOR.replace("XOR", x))
