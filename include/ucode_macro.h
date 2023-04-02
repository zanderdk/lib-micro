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
    (((src0_id) & 0xffUL) << 24) | (((src0_id) & 0x1f00)<< 10) | (((src0_id) & 0xe000) >> 13) | (1 << 3)

#define IMM_ENCODE_SRC1(src1_id) \
    (((src1_id) & 0xffUL) << 24) | (((src1_id) & 0x1f00)<< 10) | (((src1_id) & 0xe000) >> 7) | (1 << 9)

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

#define INSTR_I0(imm) ( IMM_ENCODE_SRC0(imm) )
#define INSTR_I1(imm) ( IMM_ENCODE_SRC1(imm) )
#define INSTR_R0(src) ( SRC0_ENCODE(src) )
#define INSTR_R1(src) ( SRC1_ENCODE(src) )
#define INSTR_M0(macro) ( IMM_ENCODE_SRC0(macro) | MOD0 )
#define INSTR_M1(macro) ( IMM_ENCODE_SRC1(macro) | MOD0 )
#define INSTR_DI0(dst, imm) ( DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm) )
#define INSTR_DI1(dst, imm) ( DST_ENCODE(dst) | IMM_ENCODE_SRC1(imm) )
#define INSTR_DR0(dst, src) ( DST_ENCODE(dst) | SRC0_ENCODE(src) )
#define INSTR_DR1(dst, src) ( DST_ENCODE(dst) | SRC1_ENCODE(src) )
#define INSTR_DM0(dst, macro) ( DST_ENCODE(dst) | IMM_ENCODE_SRC0(macro) | MOD0 )
#define INSTR_DM1(dst, macro) ( DST_ENCODE(dst) | IMM_ENCODE_SRC1(macro) | MOD0 )
#define INSTR_RR(src0, src1) ( SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
#define INSTR_RI(src, imm) ( SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )
#define INSTR_IR(imm, src) ( IMM_ENCODE_SRC0(imm) | SRC1_ENCODE(src) )
#define INSTR_RM(src, macro) ( SRC0_ENCODE(src) | IMM_ENCODE_SRC1(macro) | MOD0 )
#define INSTR_MR(macro, src) ( IMM_ENCODE_SRC0(macro) | SRC1_ENCODE(src) | MOD0 )
#define INSTR_DRR(dst, src0, src1) ( DST_ENCODE(dst) | SRC0_ENCODE(src0) | SRC1_ENCODE(src1) )
#define INSTR_DRI(dst, src, imm) ( DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(imm) )
#define INSTR_DIR(dst, imm, src) ( DST_ENCODE(dst) | IMM_ENCODE_SRC0(imm) | SRC1_ENCODE(src) )
#define INSTR_DRM(dst, src, macro) ( DST_ENCODE(dst) | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(macro) | MOD0 )
#define INSTR_DMR(dst, macro, src) ( DST_ENCODE(dst) | IMM_ENCODE_SRC0(macro) | SRC1_ENCODE(src) | MOD0 )

#include "inst.h"

// stagingbuf to reg

#define LDSTGBUF_DSZ64_ASZ16_SC1_DI(dst, addr_imm) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) | IMM_ENCODE_SRC0(addr_imm) | MOD2 )

#define LDSTGBUF_DSZ64_ASZ16_SC1_DR(dst, addr_reg) \
    ( _LDSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(dst) | SRC0_ENCODE(addr_reg) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_RI(src, addr_imm) \
    ( _STADSTGBUF_DSZ64_ASZ16_SC1 | DST_ENCODE(src) | IMM_ENCODE_SRC0(addr_imm) | MOD2 )

#define STADSTGBUF_DSZ64_ASZ16_SC1_RR(src, addr_reg) \
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

#define LDZX_DSZN_ASZ32_SC1(dst, src, mode) \
    ( _DZX_DSZN_ASZ32_SC1 | DST_ENCODE(dst) | ((mode) << 18) | SRC0_ENCODE(src) | MOD1 )

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


#define SFENCE _SFENCE

#define READUIP_REGOVR0(dst) \
    ( _READUIP_REGOVR | DST_ENCODE(dst) | SRC0_ENCODE(0x10) )

#define READUIP_REGOVR1(dst) \
    ( _READUIP_REGOVR | DST_ENCODE(dst) | SRC0_ENCODE(0x10) | MOD0 )

//wtf both are imm, huh but imm 0 though
#define SAVEUIP0_DI(dst, addr)                                  \
    ( _SAVEUIP | DST_ENCODE(dst) | IMM_ENCODE_SRC1( (addr) ) | IMM_ENCODE_SRC0(0)  )

#define SAVEUIP1_DI(dst, addr)                                  \
    ( _SAVEUIP | DST_ENCODE(dst) | IMM_ENCODE_SRC1( (addr) ) | IMM_ENCODE_SRC0(0)  | MOD0 )

#define SAVEUIP0_I(addr) SAVEUIP0_DI(0, addr)
#define SAVEUIP1_I(addr) SAVEUIP1_DI(0, addr)

#define SAVEUIP_REGOVR0(imm) \
    ( _SAVEUIP_REGOVR | IMM_ENCODE_SRC1(imm) )
#define SAVEUIP_REGOVR1(imm) \
    ( _SAVEUIP_REGOVR | IMM_ENCODE_SRC1(imm) | MOD0 )

#define UPDATEUSTATE_I(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) )

#define UPDATEUSTATE_NOT_I(testbits)        \
    ( _UPDATEUSTATE | IMM_ENCODE_SRC1(testbits) | MOD0 )

#define UPDATEUSTATE_RI(src, testbits)        \
    ( _UPDATEUSTATE | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(testbits) )

#define UPDATEUSTATE_NOT_RI(src, testbits)        \
    ( _UPDATEUSTATE | SRC0_ENCODE(src) | IMM_ENCODE_SRC1(testbits) | MOD0 )

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
    ( TESTUSTATE_UCODE(UST_MSLOOPCTR_NONZERO) )

#define URET0 \
    ( _URET )

#define URET1 \
    ( _URET | MOD0 )

#define UNK256 ( (0x256UL << 32) | MOD1 )

#define FLOW_CTRL_UNK       0x01
#define FLOW_CTRL_URET0     0x0a
#define FLOW_CTRL_URET1     0x0b
#define FLOW_CTRL_LDAT_IN   0x0d
#define FLOW_CTRL_MSLOOPCTR 0x0e
#define FLOW_CTRL_USTATE    0x0f

#define UFLOWCTRL_DRC(dst, reg, uop) \
    ( _UFLOWCTRL | DST_ENCODE(dst) | (((uop)&0xff)<<24) | SRC1_ENCODE(reg) )

#define UFLOWCTRL_RC(dst, reg, uop) \
    ( UFLOWCTRL_DRC(0, reg, uop) )

#define AETTRACE_DCR(dst, val, src) \
    ( _AETTRACE | DST_ENCODE(dst) | (((val)&0x1f)<<18) | SRC1_ENCODE(src) )

#define AETTRACE_DCM(dst, val, macro) \
    ( _AETTRACE | DST_ENCODE(dst) | (((val)&0x1f)<<18) | IMM_ENCODE_SRC1(macro) | MOD0 )


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
