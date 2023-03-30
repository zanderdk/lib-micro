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

#define CRC_UOP_MASK 0x3FFFFFFFFFFFUL
#define CRC_SEQ_MASK 0xFFFFFFFUL

#define IMM_ENCODE_SRC0(src0_id) \
    ( (((src0_id) & 0xffUL) << 24) | (((src0_id) & 0x1f00)<< 10) | (((src0_id) & 0xe000) >> 13) | (1 << 3) )

#define IMM_ENCODE_SRC1(src1_id) \
    ( (((src1_id) & 0xffUL) << 24) | (((src1_id) & 0x1f00)<< 10) | (((src1_id) & 0xe000) >> 7) | (1 << 9) )

#define SRC0_ENCODE(val) \
    (((val) & 0x3f) << 0)

#define SRC1_ENCODE(val) \
    (((val) & 0x3f) << 6)

#define DST_ENCODE(val) \
    (((val) & 0x3f) << 12)

#define CRC_SEQ(seq) \
    (( (seq) & CRC_SEQ_MASK) | ((parity0((seq)&CRC_SEQ_MASK) << 28) | (parity1((seq)&CRC_SEQ_MASK) << 29)))

#define CRC_UOP(uop) \
    (( (uop) & CRC_UOP_MASK) | (parity0((uop)&CRC_UOP_MASK) << 46) | (parity1((uop)&CRC_UOP_MASK) << 47))

#define UJMP(uaddr) \
    (_UJMP | IMM_ENCODE_SRC1(uaddr))

// reg to reg

#define MOVE_DSZ64_REG(dst, reg) \
    ( _MOVE_DSZ64 | DST_ENCODE(dst) | SRC0_ENCODE(reg) )

// imm to reg

#define ZEROEXT_DSZ64(dst, imm) \
    ( _ZEROEXT_DSZ64 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm))

#define ZEROEXT_DSZ32(dst, imm) \
    ( _ZEROEXT_DSZ32 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm))

#define ZEROEXT_DSZ16(dst, imm) \
    ( _ZEROEXT_DSZ16 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm))

#define ZEROEXT_DSZ8(dst, imm) \
    ( _ZEROEXT_DSZ8 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm))

#define MOVE_DSZ64_IMM(dst, imm) \
    ( _MOVE_DSZ64 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm))

// creg to reg

#define MOVEFROMCREG_DSZ64_IMM(dst, creg_imm) \
    ( _MOVEFROMCREG_DSZ64 | DST_ENCODE(dst) | IMM_ENCODE_SRC1(creg_imm) | MOD2)

#define MOVEFROMCREG_DSZ64_REG(dst, creg_reg) \
    ( _MOVEFROMCREG_DSZ64 | DST_ENCODE(dst) | SRC1_ENCODE(creg_reg) | MOD2)

#define MOVETOCREG_DSZ64_IMM(src, creg_imm) \
    ( _MOVETOCREG_DSZ64 | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(creg_imm) | MOD2)

#define MOVETOCREG_DSZ64_REG(src, creg_reg) \
    ( _MOVETOCREG_DSZ64 | SRC0_ENCODE(src) | SRC1_ENCODE(creg_reg) | MOD2)

// uram to reg

#define READURAM_IMM(dst, addr_imm) \
    ( _READURAM | DST_ENCODE(dst) | IMM_ENCODE_SRC1(addr_imm) | MOD2 )

#define READURAM_REG(dst, addr_reg) \
    ( _READURAM | DST_ENCODE(dst) | SRC1_ENCODE(addr_reg) | MOD2 )

#define WRITEURAM_IMM(src, addr_imm) \
    ( _WRITEURAM | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(addr_imm) | MOD2 )

#define WRITEURAM_REG(src, addr_reg) \
    ( _WRITEURAM | SRC0_ENCODE(src) | SRC1_ENCODE(addr_reg) | MOD2 )

// stagingbuf to reg

#define LDSTGBUF_DSZ64_ASZ16_SC1_IMM(dst, addr_imm) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(addr_imm) | MOD2 )

#define LDSTGBUF_DSZ64_ASZ16_SC1_REG(dst, addr_reg) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) | SRC0_ENCODE(addr_reg) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_IMM(src, addr_imm) \
    ( _STADSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(src) | IMM_ENCODE_SRC0(addr_imm) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_REG(src, addr_reg) \
    ( _STADSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(src) | SRC0_ENCODE(addr_reg) | MOD2 )

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

// test read ram

#define LDTICKLE_DSZ64_ASZ32_SC1(dst, seg, src, mode) \
    ( _LDTICKLE_DSZ64_ASZ32_SC1 | DST_ENCODE(dst) | ((seg) << 36) | ((mode) << 18) | SRC0_ENCODE(src) )



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

//wtf both are imm, huh but imm 0 though
#define SAVEUIP0(addr)                                  \
    ( _SAVEUIP | IMM_ENCODE_SRC1( addr ) | IMM_ENCODE_SRC0(0)  )

#define SAVEUIP1(addr)                                  \
    ( _SAVEUIP | IMM_ENCODE_SRC1( addr ) | IMM_ENCODE_SRC0(0)  | MOD0 ) //mod controlls if SAVEUIP1

#define SAVEUIP0_DST(dst, addr)                                  \
    ( _SAVEUIP | DST_ENCODE(dst) | IMM_ENCODE_SRC1( (addr) ) | IMM_ENCODE_SRC0(0)  )

#define SAVEUIP1_DST(dst, addr)                                  \
    ( _SAVEUIP | DST_ENCODE(dst) | IMM_ENCODE_SRC1( (addr) ) | IMM_ENCODE_SRC0(0)  | MOD0 ) //mod controlls if SAVEUIP1

#define UST_MSLOOPCTR_NONZERO 1

#define WRMSLOOPCTRFBR(x) \
    ( _WRMSLOOPCTRFBR | IMM_ENCODE_SRC1(x) )

#define UPDATEUSTATE_UCODE(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) )

#define UPDATEUSTATE_SYS(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 )

#define UPDATEUSTATE_VMX(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD2)

#define UPDATEUSTATE_UCODE_NOT(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD0 )

#define UPDATEUSTATE_SYS_NOT(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD0 )

#define UPDATEUSTATE_VMX_NOT(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD2 | MOD0 )

#define TESTUSTATE_UCODE(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) )

#define TESTUSTATE_SYS(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 )

#define TESTUSTATE_VMX(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD2 )

#define TESTUSTATE_UCODE_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) | MOD0 )

#define TESTUSTATE_SYS_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD0 )

#define TESTUSTATE_VMX_NOT(testbits)        \
    ( _TESTUSTATE | IMM_ENCODE_SRC1(testbits) | MOD1 | MOD2 | MOD0 )

#define TESTUSTATE_MSLOOP \
    ( TESTUSTATE_UCODE(1) )

#define URET0 \
    ( _URET )

#define URET1 \
    ( _URET | MOD0 )

#define UNK256 ( (0x256UL << 32) | MOD1 )

#define FLOW_CTRL_UNK (0x01 << 24)
#define FLOW_CTRL_URET0 (0x0a << 24)
#define FLOW_CTRL_URET1 (0x0b << 24)
#define FLOW_CTRL_LDAT_IN (0x0d << 24)
#define FLOW_CTRL_MSLOOPCTR (0x0e << 24)
#define FLOW_CTRL_USTATE (0x0f << 24)

#define UFLOWCTRL_REG(reg, uop) \
    ( _UFLOWCTRL | uop | SRC1_ENCODE(reg) )

//Sequence word here:

#define SEQ_UADDR(addr) ( ((addr) & 0x7fffUL) << 8 )

#define SEQ_UP0(u)      ( ((u) & 0b11) << 0 )
#define SEQ_UP1(u)      ( ((u) & 0b11) << 6 )
#define SEQ_UP2(u)      ( ((u) & 0b11) << 23 )

#define SEQ_EFLOW(x)    ( ((x) & 0b1111) << 2 )
#define SEQ_SYNC(x)     ( ((x) & 0b111) << 25 )

// idx controls which uop in triad to target

#define SEQ_URET0(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0x2) )
#define SEQ_URET1(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0x3) )
#define SEQ_SAVEUIP0(idx)           ( SEQ_UP0(idx) | SEQ_EFLOW(0x4) )
#define SEQ_SAVEUIP1(idx)           ( SEQ_UP0(idx) | SEQ_EFLOW(0x5) )
#define SEQ_SAVEUIP0_REGOVR(idx)    ( SEQ_UP0(idx) | SEQ_EFLOW(0x6) )
#define SEQ_SAVEUIP1_REGOVR(idx)    ( SEQ_UP0(idx) | SEQ_EFLOW(0x7) )
#define SEQ_WRTAGW(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0x8) )
#define SEQ_MSLOOP(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0x9) )
#define SEQ_MSSTOP(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0xb) )
#define SEQ_UEND0(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xc) )
#define SEQ_UEND1(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xd) )
#define SEQ_UEND2(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xe) )
#define SEQ_UEND3(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xf) )

#define SEQ_GOTO0(addr)     ( SEQ_UP1(0) | SEQ_UADDR(addr) )
#define SEQ_GOTO1(addr)     ( SEQ_UP1(1) | SEQ_UADDR(addr) )
#define SEQ_GOTO2(addr)     ( SEQ_UP1(2) | SEQ_UADDR(addr) )

#define SEQ_LFNCEWAIT(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(1) )
#define SEQ_LFNCEMARK(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(2) )
#define SEQ_LFNCEWTMRK(idx) ( SEQ_UP2(idx) | SEQ_SYNC(3) )
#define SEQ_SYNCFULL(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(4) )
#define SEQ_SYNCWAIT(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(5) )
#define SEQ_SYNCMARK(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(6) )
#define SEQ_SYNCWTMRK(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(7) )

// shortcuts
#define SEQ_NEXT    SEQ_UP1(3)
#define SEQ_NOSYNC  SEQ_UP2(3)

#define NOP_SEQWORD ( SEQ_NEXT | SEQ_NOSYNC )
#define END_SEQWORD ( SEQ_UEND0(2) | SEQ_NEXT | SEQ_LFNCEWAIT(2) )

// helpers
#define PUSHREG(src) \
    SUB_DSZ64_IMM(RSP, RSP, 0x8), MOVE_DSZ64_REG(TMP0, src), STAD_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL)

#define PUSHCREG(creg) \
    SUB_DSZ64_IMM(RSP, RSP, 0x8), MOVEFROMCREG_DSZ64(TMP0, creg), STAD_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL)

#define POPREG(dst) \
    LDZX_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL), MOVE_DSZ64_REG(dst, TMP0), ADD_DSZ64_IMM(RSP, RSP, 0x8)

#define POPCREG(creg) \
    LDZX_DSZ64_ASZ32_SC1(TMP0, 0x3UL, RSP, 0x1aUL), MOVETOCREG_DSZ64(TMP0, creg), ADD_DSZ64_IMM(RSP, RSP, 0x8)

#endif // UCODE_MACRO_H_