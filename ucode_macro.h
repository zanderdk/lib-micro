#ifndef UCODE_MACRO_H_
#define UCODE_MACRO_H_

#include "opcode.h"

#define END_UNKOWN_UOP (0x125600000000uL)
#define NOP_SEQWORD (0x0000300000c0uL)
#define END_SEQWORD (0x130000f2)

#define MOD0 (1UL << 23)
#define MOD1 (1UL << 44)
#define MOD2 (1UL << 45)

__attribute__((always_inline))
static inline u64 parity0(u64 value) {
    u64 parity = 0;
    while (value) {
        parity ^= (value & 1);
        value = value >> 2;
    }
    return parity;
}

__attribute__((always_inline))
static inline u64 parity1(u64 value) {
    u64 parity = 0;
    value = value >> 1;
    while (value) {
        parity ^= (value & 1);
        value = value >> 2;
    }
    return parity;
}

// generic stuff

#define CRC_UOP_MASK 0x3FFFFFFFFFFFLU
#define CRC_SEQ_MASK 0xFFFFFFFLU

#define IMM_ENCODE_SRC0(src0_id) \
    ((src0_id & 0xffUL) << 24) | ((src0_id & 0x1f00)<< 10) | ((src0_id & 0xe000) >> 13) | (1 << 3)

#define IMM_ENCODE_SRC1(src1_id) \
    ((src1_id & 0xffUL) << 24) | ((src1_id & 0x1f00)<< 10) | ((src1_id & 0xe000) >> 7) | (1 << 9)

#define SRC0_ENCODE(val) \
    ((val & 0x3f) << 0)

#define SRC1_ENCODE(val) \
    ((val & 0x3f) << 6)

#define DST_ENCODE(val) \
    ((val & 0x3f) << 12)

#define CRC_SEQ(seq) \
    (( (seq) & CRC_SEQ_MASK) | ((parity0(seq) << 28) | (parity1(seq) << 29)))

#define CRC_UOP(uop) \
    (( (uop) & CRC_UOP_MASK) | (parity1(uop) << 47) | (parity0(uop) << 46))

#define UJMP(uaddr) \
    CRC_UOP(_UJMP | IMM_ENCODE_SRC1( (uaddr) ))

// generic moves

#define MOVE_DSZ64(dst) \
    ( _MOVE_DSZ64 | DST_ENCODE(dst) )

#define MOVEFROMCREG_DSZ64(dst) \
    ( _MOVEFROMCREG_DSZ64 | DST_ENCODE(dst) )

#define LDSTGBUF_DSZ64_ASZ16_SC1(dst) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) )

// reg to reg

#define MOVEFROMCREG_DSZ64_REG(dst, crreg)             \
    CRC_UOP( MOVEFROMCREG_DSZ64(dst) | IMM_ENCODE_SRC1( (crreg) ))

#define MOVE_DSZ64_REG(dst, reg)                                           \
    CRC_UOP( MOVE_DSZ64(dst) | SRC0_ENCODE( (reg) ) | SRC1_ENCODE( (reg) ) )

// imm to reg

#define MOVE_DSZ64_IMM(dst, imm)                                           \
    CRC_UOP( MOVE_DSZ64(dst) | IMM_ENCODE_SRC0( (imm) ))

// uram/stagingbuf to reg

#define READURAM(dst, imm) \
    CRC_UOP( _READURAM | DST_ENCODE(dst) | IMM_ENCODE_SRC1(imm) | MOD2 )

//TODO: cant write higer than 0x8c have no idea why
#define WRITEURAM(src, off) \
    CRC_UOP( _WRITEURAM | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(off) | MOD2 )

#define LDSTGBUF_DSZ64_ASZ16_SC1_REG(dst, off)             \
    CRC_UOP( LDSTGBUF_DSZ64_ASZ16_SC1(dst) | IMM_ENCODE_SRC0( (off) ) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_REG(src, off)             \
    CRC_UOP( _STADSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(src) | IMM_ENCODE_SRC0(off) | MOD2 )

//normal ram to reg

/**
 * somehow mode is related to segment selector mode 0x0a and 0x1a is good for rsp and SS stuff
 * while 0x08 and 0x18 is related to general purpose and DS selector
 *
 * it could be that 0x0 is implicit DS
 * i am quite sure 0x1 is DS
 * 0x02 could be CS but not at all sure
 **/

/* mode = (uop & 0x7c0000) >> 18 */
/* seg_sel = (uop & 0x003000000000) >> 36 */

#define LDZX_DSZ64_ASZ32_SC1(dst, seg, src, mode) \
    CRC_UOP( _LDZX_DSZ64_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ32_ASZ32_SC1(dst, seg, src, mode) \
    CRC_UOP( _LDZX_DSZ32_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ16_ASZ32_SC1(dst, seg, src, mode) \
    CRC_UOP( _LDZX_DSZ16_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ8_ASZ32_SC1(dst, seg, src, mode) \
    CRC_UOP( _LDZX_DSZ8_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

// write normal ram
#define STAD_DSZ64_ASZ32_SC1(src2, seg, src, mode) \
    CRC_UOP( _STAD_DSZ64_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ32_ASZ32_SC1(src2, seg, src, mode) \
    CRC_UOP( _STAD_DSZ32_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ16_ASZ32_SC1(src2, seg, src, mode) \
    CRC_UOP( _STAD_DSZ16_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ8_ASZ32_SC1(src2, seg, src, mode) \
    CRC_UOP( _STAD_DSZ8_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

//this mode has a wacked encoding and not sure 100p working
#define LDZX_DSZN_ASZ32_SC1(dst, src, mode) \
    CRC_UOP( _DZX_DSZN_ASZ32_SC1 | DST_ENCODE(dst) | ((mode) << 18) | SRC0_ENCODE(src) | MOD1 )

#include "alu_ops.h"

#endif // UCODE_MACRO_H_
