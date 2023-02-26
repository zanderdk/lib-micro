#ifndef UCODE_MACRO_H_
#define UCODE_MACRO_H_

#include "opcode.h"

#define MOD0 (1UL << 23)
#define MOD1 (1UL << 44)
#define MOD2 (1UL << 45)

__attribute__((always_inline))
static inline unsigned long long parity0(unsigned long long value) {
    unsigned long long parity = 0;
    while (value) {
        parity ^= (value & 1);
        value = value >> 2;
    }
    return parity;
}

__attribute__((always_inline))
static inline unsigned long long parity1(unsigned long long value) {
    unsigned long long parity = 0;
    value = value >> 1;
    while (value) {
        parity ^= (value & 1);
        value = value >> 2;
    }
    return parity;
}

// generic stuff

#define CRC_UOP_MASK 0xFFFFFFFFFFFFLU
#define CRC_SEQ_MASK 0x3FFFFFFFUL

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
    (( (uop) & CRC_UOP_MASK) | (parity0(uop) << 46) | (parity1(uop) << 47))

#define UJMP(uaddr) \
    (_UJMP | IMM_ENCODE_SRC1( (uaddr) ))

// generic moves

#define MOVE_DSZ64(dst) \
    ( _MOVE_DSZ64 | DST_ENCODE(dst) )

#define MOVEFROMCREG_DSZ64(dst) \
    ( _MOVEFROMCREG_DSZ64 | DST_ENCODE(dst) )

#define LDSTGBUF_DSZ64_ASZ16_SC1(dst) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) )

// reg to reg

#define MOVEFROMCREG_DSZ64_REG(dst, crreg)             \
    ( MOVEFROMCREG_DSZ64(dst) | IMM_ENCODE_SRC1( (crreg) ))

#define MOVETOCREG_DSZ64(reg, crreg)             \
    ( _MOVETOCREG_DSZ64 | SRC0_ENCODE( (reg) ) | IMM_ENCODE_SRC1( (crreg) ))

#define MOVE_DSZ64_REG(dst, reg)                                           \
    ( MOVE_DSZ64(dst) | SRC0_ENCODE( (reg) ) | SRC1_ENCODE( (reg) ) )

// imm to reg

#define ZEROEXT_DSZ64(dst, imm) \
    ( _ZEROEXT_DSZ64(dst) | IMM_ENCODE_SRC0( (imm) ))

#define ZEROEXT_DSZ32(dst, imm) \
    ( _ZEROEXT_DSZ32(dst) | IMM_ENCODE_SRC0( (imm) ))

#define ZEROEXT_DSZ16(dst, imm) \
    ( _ZEROEXT_DSZ16(dst) | IMM_ENCODE_SRC0( (imm) ))

#define ZEROEXT_DSZ8(dst, imm) \
    ( _ZEROEXT_DSZ8(dst) | IMM_ENCODE_SRC0( (imm) ))

#define MOVE_DSZ64_IMM(dst, imm)                                           \
    ( MOVE_DSZ64(dst) | IMM_ENCODE_SRC0( (imm) ))

// uram/stagingbuf to reg

#define READURAM(dst, imm) \
    ( _READURAM | DST_ENCODE(dst) | IMM_ENCODE_SRC1(imm) | MOD2 )

//TODO: cant write higer than 0x8c have no idea why
#define WRITEURAM(src, off) \
    ( _WRITEURAM | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(off) | MOD2 )

#define LDSTGBUF_DSZ64_ASZ16_SC1_REG(dst, off)             \
    ( LDSTGBUF_DSZ64_ASZ16_SC1(dst) | IMM_ENCODE_SRC0( (off) ) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_REG(src, off)             \
    ( _STADSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(src) | IMM_ENCODE_SRC0(off) | MOD2 )

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
    ( _LDZX_DSZ64_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ32_ASZ32_SC1(dst, seg, src, mode) \
    ( _LDZX_DSZ32_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ16_ASZ32_SC1(dst, seg, src, mode) \
    ( _LDZX_DSZ16_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define LDZX_DSZ8_ASZ32_SC1(dst, seg, src, mode) \
    ( _LDZX_DSZ8_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

// write normal ram
#define STAD_DSZ64_ASZ32_SC1(src2, seg, src, mode) \
    ( _STAD_DSZ64_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ32_ASZ32_SC1(src2, seg, src, mode) \
    ( _STAD_DSZ32_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ16_ASZ32_SC1(src2, seg, src, mode) \
    ( _STAD_DSZ16_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

#define STAD_DSZ8_ASZ32_SC1(src2, seg, src, mode) \
    ( _STAD_DSZ8_ASZ32_SC1 | DST_ENCODE(src2) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )

//this mode has a wacked encoding and not sure 100p working
#define LDZX_DSZN_ASZ32_SC1(dst, src, mode) \
    ( _DZX_DSZN_ASZ32_SC1 | DST_ENCODE(dst) | ((mode) << 18) | SRC0_ENCODE(src) | MOD1 )

#include "alu_ops.h"

#define SAVEUIP0(addr) \
    ( _SAVEUIP | SRC0_ENCODE(0) | IMM_ENCODE_SRC0(addr) )

#define SAVEUIP1(addr) \
    ( _SAVEUIP | SRC0_ENCODE(1) | IMM_ENCODE_SRC0(addr) )

#define UST_MSLOOPCTR_NONZERO 1

#define WRMSLOOPCTRFBR(x) \
    ( _WRMSLOOPCTRFBR | IMM_ENCODE_SRC1(x) )

#define TESTUSTATE_UCODE(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) )

#define TESTUSTATE_SYS(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC0(testbits) | MOD1 )

#define TESTUSTATE_VMX(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC0(testbits) | MOD1 | MOD2 )

#define TESTUSTATE_UCODE_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC0(testbits) | MOD0 )

#define TESTUSTATE_SYS_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC0(testbits) | MOD1 | MOD0 )

#define TESTUSTATE_VMX_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC0(testbits) | MOD1 | MOD2 | MOD0 )

#define TESTUSTATE_MSLOOP \
    ( TESTUSTATE_UCODE(1) )

#define SEQ_UADDR(addr) \
    ( (addr & 0x7fffUL) << 8 )

#define SEQ_UP0(u) ( (u & 0b11) << 0 )
#define SEQ_UP1(u) ( (u & 0b11) << 6 )
#define SEQ_UP2(u) ( (u & 0b11) << 23 )

#define SEQ_EFLOW(x) (  (x & 0b1111) << 2 )
#define SEQ_SYNC(x) (  (x & 0b111) << 25 )

#define SEQ_CTRL0  ( SEQ_UP0(0) )
#define SEQ_CTRL1  ( SEQ_UP0(1) )
#define SEQ_CTRL2  ( SEQ_UP0(2) )

/* #define SEQ_END0  ( SEQ_UP1(0) ) */
/* #define SEQ_END1  ( SEQ_UP1(1) ) */
/* #define SEQ_END2  ( SEQ_UP1(2) ) */

#define SEQ_SYNC0  ( SEQ_UP2(0) )
#define SEQ_SYNC1  ( SEQ_UP2(1) )
#define SEQ_SYNC2  ( SEQ_UP2(2) )

#define NO_SYNC SEQ_UP2(3)

//CTRL idx controls URET UEND USAVEUIP
//END idx controls GOTO
//SYNC idx controls sync doh

#define SEQ_SEQUENTIAL (SEQ_SYNC(0))

#define SEQ_LFNCEWAIT  (SEQ_SYNC(1))
#define SEQ_LFNCEMARK  (SEQ_SYNC(2))
#define SEQ_LFNCEWTMRK (SEQ_SYNC(3))

#define SEQ_SYNCFULL   (SEQ_SYNC(4))
#define SEQ_SYNCWAIT   (SEQ_SYNC(5))
#define SEQ_SYNCMARK   (SEQ_SYNC(6))
#define SEQ_SYNCWTMRK  (SEQ_SYNC(7))

#define SEQ_WRTAGW     (SEQ_EFLOW(8))
#define SEQ_MSLOOP     (SEQ_EFLOW(9))
#define SEQ_MSSTOP     (SEQ_EFLOW(0xb))

#define SEQ_GOTO0(addr) \
    ( SEQ_CTRL0 | SEQ_UP1(0) | NO_SYNC | SEQ_UADDR(addr) )

#define SEQ_GOTO1(addr) \
    ( SEQ_CTRL0 | SEQ_UP1(1) | NO_SYNC | SEQ_UADDR(addr) )

#define SEQ_GOTO2(addr) \
    ( SEQ_CTRL0 | SEQ_UP1(2) | NO_SYNC | SEQ_UADDR(addr) )

#define SEQ_UEND0(idx) \
    ( SEQ_UP0(idx) | SEQ_EFLOW(0xc) | SEQ_SYNC(1) )

#define SEQ_UEND1(idx) \
    ( SEQ_UP0(idx) | SEQ_EFLOW(0xd) | SEQ_SYNC(1) )

#define SEQ_UEND3(idx) \
    ( SEQ_UP0(idx) | SEQ_EFLOW(0xe) | SEQ_SYNC(1) )

#define SEQ_UEND4(idx) \
    ( SEQ_UP0(idx) | SEQ_EFLOW(0xf) | SEQ_SYNC(1) )

#define SEQ_UEND0_0 \
    ( SEQ_UEND0(0) )

#define SEQ_UEND0_1 \
    ( SEQ_UEND0(1) )

#define SEQ_UEND0_2 \
    ( SEQ_UEND0(2) )

#define SEQ_URET0_0 \
    ( SEQ_UP0(0) | SEQ_EFLOW(0x2) | SEQ_SYNC(1) )

#define SEQ_URET0_1 \
    ( SEQ_UP0(1) | SEQ_EFLOW(0x2) | SEQ_SYNC(1) )

#define SEQ_URET0_2 \
    ( SEQ_UP0(2) | SEQ_EFLOW(0x2) | SEQ_SYNC(1) )

#define SEQ_URET1_0 \
    ( SEQ_UP0(0) | SEQ_EFLOW(0x3) | SEQ_SYNC(1) )

#define SEQ_URET1_1 \
    ( SEQ_UP0(1) | SEQ_EFLOW(0x3) | SEQ_SYNC(1) )

#define SEQ_URET1_2 \
    ( SEQ_UP0(2) | SEQ_EFLOW(0x3) | SEQ_SYNC(1) )

#define NOP_SEQWORD (0x0000300000c0uL)
#define END_SEQWORD (0x130000f2)

#define END_UNKOWN_UOP (0x125600000000uL)

// helpers
#define PUSHREG(src) \
	SUB_DSZ64_IMM(RSP, RSP, 0x8), MOVE_DSZ64_REG(TMP0, src), STAD_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL)

#define PUSHCREG(creg) \
	SUB_DSZ64_IMM(RSP, RSP, 0x8), MOVEFROMCREG_DSZ64_REG(TMP0, creg), STAD_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL)

#define POPREG(dst) \
    LDZX_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL), MOVE_DSZ64_REG(dst, TMP0), ADD_DSZ64_IMM(RSP, RSP, 0x8)

#define POPCREG(creg) \
    LDZX_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL), MOVETOCREG_DSZ64(TMP0, creg), ADD_DSZ64_IMM(RSP, RSP, 0x8)

#endif // UCODE_MACRO_H_
