#ifndef UCODE_MACRO_H_
#define UCODE_MACRO_H_

#define END_UNKOWN_UOP (0x125600000000uL)
#define NOP_SEQWORD (0x0000300000c0uL)
#define END_SEQWORD (0x130000f2)

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

#define CRC_UOP_MASK 0x3FFFFFFFFFFFLU
#define CRC_SEQ_MASK 0xFFFFFFFLU

#define IMM_ENCODE(imm_val) \
    ((imm_val & 0xff) << 24) | ((imm_val & 0x1f00)<< 10) | ((imm_val & 0xe000) >> 7) | (1 << 9)

#define CRC_SEQ(seq) \
    (seq | ((parity0(seq) << 28) | (parity1(seq) << 29)))

#define CRC_UOP(uop) \
    (uop | (parity1(uop) << 45) | (parity0(uop) << 46))

#define UJMP(uaddr) \
    CRC_UOP(_UJMP | IMM_ENCODE((uaddr)))

#define MOVE_DSZ64 \
    CRC_UOP(_MOVE_DSZ64 | IMM_ENCODE((uaddr)))

#endif // UCODE_MACRO_H_
