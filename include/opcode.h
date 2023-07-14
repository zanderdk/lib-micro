#ifndef OPCODE_H_
#define OPCODE_H_

// registers
#define RAX     0x20UL
#define RCX     0x21UL
#define RDX     0x22UL
#define RBX     0x23UL
#define RSP     0x24UL
#define RBP     0x25UL
#define RSI     0x26UL
#define RDI     0x27UL
#define R8      0x28UL
#define R9      0x29UL
#define R10     0x2aUL
#define R11     0x2bUL
#define R12     0x2cUL
#define R13     0x2dUL
#define R14     0x2eUL
#define R15     0x2fUL
#define TMP0    0x30UL
#define TMP1    0x31UL
#define TMP2    0x32UL
#define TMP3    0x33UL
#define TMP4    0x34UL
#define TMP5    0x35UL
#define TMP6    0x36UL
#define TMP7    0x37UL
#define TMP8    0x38UL
#define TMP9    0x39UL
#define TMP10   0x3aUL
#define TMP11   0x3bUL
#define TMP12   0x3cUL
#define TMP13   0x3dUL
#define TMP14   0x3eUL
#define TMP15   0x3fUL
#define XMM0    0x20UL
#define XMM1    0x21UL
#define XMM2    0x22UL
#define XMM3    0x23UL
#define XMM4    0x24UL
#define XMM5    0x25UL
#define XMM6    0x26UL
#define XMM7    0x27UL
#define XMM8    0x28UL
#define XMM9    0x29UL
#define XMM10   0x2aUL
#define XMM11   0x2bUL
#define XMM12   0x2cUL
#define XMM13   0x2dUL
#define XMM14   0x2eUL
#define XMM15   0x2fUL
#define MM0     0x30UL
#define MM1     0x31UL
#define MM2     0x32UL
#define MM3     0x33UL
#define MM4     0x34UL
#define MM5     0x35UL
#define MM6     0x36UL
#define MM7     0x37UL
#define TMM0    0x38UL
#define TMM1    0x39UL
#define TMM2    0x3aUL
#define TMM3    0x3bUL
#define TMM4    0x3cUL
#define TMM5    0x3dUL
#define TMM6    0x3eUL
#define TMM7    0x3fUL
#define R64DST  0x01UL
#define R64SRC  0x02UL
#define R64BASE 0x04UL
#define R64IDX  0x05UL
#define TMPV0   0x14UL
#define TMPV1   0x15UL
#define TMPV2   0x16UL
#define TMPV3   0x17UL

// control registers
#define CORE_CR_CUR_RIP 0x67UL
#define CORE_CR_CUR_UIP 0x68UL
#define UCODE_CR_SE_SVN_KEY_0 0x205UL
#define UCODE_CR_SE_SVN_KEY_1 0x206UL
#define CTAP_CR_PPPE_TAP_STATUS 0x208UL
#define CTAP_CR_TAP_CONFIG 0x285UL
#define UCODE_CR_X2APIC_TPR 0x288UL
#define UCODE_CR_X2APIC_EOI 0x28bUL
#define UCODE_CR_PPPE_EVENT_RESET 0x29eUL
#define UCODE_CR_PPPE_EVENT_STATUS 0x29fUL
#define CTAP_CR_PDR_T0_LOW 0x2c0UL
#define CTAP_CR_PDR_T0_HIGH 0x2c1UL
#define ML3_CR_PIC_GLOBAL_EVENT_INHIBIT 0x2c4UL
#define CTAP_CR_PROBE_MODE 0x2cdUL
#define X86_CR_THREAD_ID 0x2b9UL
#define ROB1_CR_ICECTLPMR 0x2dfUL
#define ML3_CR_PIC_DEBUG_MODES 0x2e6UL
#define PMH_CR_BRAM_BASE 0x51bUL
#define PMH_CR_CR3 0x529UL
#define PMH_CR_ELSRR_BASE 0x555UL
#define PMH_CR_ELSRR_MASK 0x556UL
#define PMH_CR_EPCM_BASE 0x557UL
#define PMH_CR_EMRR_BASE 0x562UL
#define PMH_CR_EMRR_MASK 0x563UL
#define PMH_CR_EMXRR_BASE 0x564UL
#define PMH_CR_EMXRR_MASK 0x565UL
#define PMH_CR_SMRR_BASE 0x572UL
#define PMH_CR_SMRR_MASK 0x573UL
#define PMH_CR_PRMRR_BASE 0x574UL
#define PMH_CR_PRMRR_MASK 0x575UL
#define MS_CR_DEBUG_DEFEATURE 0x692UL
#define XU_CR_MACROINSTRUCTION_ALIAS 0x752UL
#define CORE_CR_CR4 0x7c5UL
#define BAC_CR_CS_BASE 0x78eUL
#define UCODE_CR_XU_USTATE_CTRL 0x7c6UL
#define CORE_CR_CR0 0x7f6UL
#define CORE_CR_DEBUGCTL 0x7f9UL
#define CORE_CR_EFLAGS 0x7feUL

// macro imms
#define IMM_MACRO_ALIAS_DISPLACEMENT    0x00UL
#define IMM_MACRO_ALIAS_IMMEDIATE       0x00UL
#define IMM_MACRO_ALIAS_RIP             0x04UL
#define IMM_MACRO_ALIAS_STI             0x05UL
#define IMM_MACRO_ALIAS_MSLOOPCTR       0x08UL
#define IMM_MACRO_ALIAS_DATASIZE        0x0bUL
#define IMM_MACRO_ALIAS_INSTRUCTION     0x10UL

// ustate UCODE
#define UST_MSLOOPCTR_NONZERO   0x0001UL
#define UST_SMM                 0x0800UL

// ustate SYS
#define UST_VMX_DIS         0x0001UL
#define UST_USER_MODE       0x0002UL
#define UST_8086_MODE       0x0004UL
#define UST_OP_SIZE_32BIT   0x0008UL
#define UST_ADDR_SIZE_64BIT 0x0010UL
#define UST_XUCODE          0x0020UL
#define UST_SE_INIT_DONE    0x0040UL
#define UST_VMX_GUEST       0x0080UL
#define UST_VMX_OP_DIS      0x0100UL

// Segment selectors
#define SEG_PHYS 0x01UL
#define SEG_GDT  0x06UL
#define SEG_LDT  0x07UL
#define SEG_ES   0x08UL
#define SEG_CS   0x09UL
#define SEG_FS   0x0cUL
#define SEG_GS   0x0dUL
#define SEG_IDT  0x0eUL
#define SEG_TSS  0x0fUL
#define SEG_DS   0x18UL
#define SEG_SS   0x1aUL

// Segment descriptor fields
#define FLD_LIMIT_VAL    0x0UL
#define FLD_BASE         0x2UL
#define FLD_FLGS         0x4UL
#define FLD_LIMIT        0x6UL
#define FLD_SEL          0x8UL
#define FLD_SEL_FLGS_LIM 0xaUL

// opcode parts
#define _CONDO      0x000UL
#define _CONDNO     0x100UL
#define _CONDB      0x200UL
#define _CONDNB     0x300UL
#define _CONDZ      0x001UL
#define _CONDNZ     0x101UL
#define _CONDBE     0x201UL
#define _CONDNBE    0x301UL
#define _CONDS      0x002UL
#define _CONDNS     0x102UL
#define _CONDP      0x202UL
#define _CONDNP     0x302UL
#define _CONDL      0x003UL
#define _CONDNL     0x103UL
#define _CONDLE     0x203UL
#define _CONDNLE    0x303UL

#define _DSZ32  0x000UL
#define _DSZ64  0x040UL
#define _DSZ16  0x080UL
#define _DSZ8   0x0c0UL

// opcodes
#define NOP (0x0)

#define _ADD_DSZ32 (0x000UL << 32)
#define _OR_DSZ32 (0x001UL << 32)
#define _AND_DSZ32 (0x004UL << 32)
#define _SUB_DSZ32 (0x005UL << 32)
#define _XOR_DSZ32 (0x006UL << 32)
#define _NOTAND_DSZ32 (0x007UL << 32)
#define _ZEROEXT_DSZ32 (0x008UL << 32)
#define _MOVE_DSZ32 (0x009UL << 32)
/* #define _TESTUSTATE (0x04aUL << 32) */
#define _TESTUSTATE (0x00aUL << 32)
#define _UPDATEUSTATE (0x00bUL << 32)
#define _SAVEUIP (0x00cUL << 32)
#define _SAVEUIP_REGOVR (0x00dUL << 32)
#define _WRMSLOOPCTRFBR (0x00eUL << 32)
#define _BT_DSZ32 (0x014UL << 32)
#define _BTS_DSZ32 (0x015UL << 32)
#define _BTR_DSZ32 (0x016UL << 32)
#define _BTC_DSZ32 (0x017UL << 32)
#define _MJMPTARGET_INDIRECT_ASZ32 (0x01eUL << 32)
#define _CONCAT_DSZ32 (0x021UL << 32)
#define _SHL_DSZ32 (0x024UL << 32)
#define _SHR_DSZ32 (0x025UL << 32)
#define _MOVSX_SSZ32_DSZ64 (0x02aUL << 32)
#define _ROL_DSZ32 (0x02cUL << 32)
#define _ROR_DSZ32 (0x02dUL << 32)
#define _SAR_DSZ32 (0x02eUL << 32)
#define _SELECTCC_DSZ32_CONDO (0x030UL << 32)
#define _SELECTCC_DSZ32_CONDNO (0x031UL << 32)
#define _SELECTCC_DSZ32_CONDB (0x032UL << 32)
#define _SELECTCC_DSZ32_CONDNB (0x033UL << 32)
#define _CMOVCC_DSZ32_CONDO (0x034UL << 32)
#define _CMOVCC_DSZ32_CONDNO (0x035UL << 32)
#define _CMOVCC_DSZ32_CONDB (0x036UL << 32)
#define _CMOVCC_DSZ32_CONDNB (0x037UL << 32)
#define _MOVEINSERTFLGS_DSZ32 (0x03dUL << 32)
#define _ADD_DSZ64 (0x040UL << 32)
#define _OR_DSZ64 (0x041UL << 32)
#define _MOVETOCREG_DSZ64 (0x042UL << 32)
#define _WRITEURAM (0x043UL << 32)
#define _AND_DSZ64 (0x044UL << 32)
#define _SUB_DSZ64 (0x045UL << 32)
#define _XOR_DSZ64 (0x046UL << 32)
#define _NOTAND_DSZ64 (0x047UL << 32)
#define _ZEROEXT_DSZ64 (0x048UL << 32)
#define _MOVE_DSZ64 (0x049UL << 32)
/* #define _TESTUSTATE (0x04aUL << 32) */
/* #define _SAVEUIP (0x04cUL << 32) */
#define _UJMPCC_DIRECT_NOTTAKEN_CONDO (0x050UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNO (0x051UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDB (0x052UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNB (0x053UL << 32)
#define _BT_DSZ64 (0x054UL << 32)
#define _BTS_DSZ64 (0x055UL << 32)
#define _BTR_DSZ64 (0x056UL << 32)
#define _BTC_DSZ64 (0x057UL << 32)
#define _MJMPCC_DSZNOP_CONDO (0x058UL << 32)
#define _MJMPCC_DSZNOP_CONDNO (0x059UL << 32)
#define _MJMPCC_DSZNOP_CONDB (0x05aUL << 32)
#define _MJMPCC_DSZNOP_CONDNB (0x05bUL << 32)
#define _MJMPTARGET_INDIRECT_ASZ64 (0x05cUL << 32)
/* #define _MJMPTARGET_INDIRECT_ASZ64 (0x05eUL << 32) */
#define _MOVEFROMCREG_DSZ64 (0x062UL << 32)
#define _READURAM (0x063UL << 32)
#define _SHL_DSZ64 (0x064UL << 32)
#define _SHR_DSZ64 (0x065UL << 32)
#define _ROL_DSZ64 (0x06cUL << 32)
#define _ROR_DSZ64 (0x06dUL << 32)
#define _SAR_DSZ64 (0x06eUL << 32)
#define _SELECTCC_DSZ64_CONDO (0x070UL << 32)
#define _SELECTCC_DSZ64_CONDNO (0x071UL << 32)
#define _SELECTCC_DSZ64_CONDB (0x072UL << 32)
#define _SELECTCC_DSZ64_CONDNB (0x073UL << 32)
#define _CMOVCC_DSZ64_CONDO (0x074UL << 32)
#define _CMOVCC_DSZ64_CONDNO (0x075UL << 32)
#define _CMOVCC_DSZ64_CONDB (0x076UL << 32)
#define _CMOVCC_DSZ64_CONDNB (0x077UL << 32)
#define _MOVEINSERTFLGS_DSZ64 (0x07dUL << 32)
#define _ADD_DSZ16 (0x080UL << 32)
#define _OR_DSZ16 (0x081UL << 32)
#define _AND_DSZ16 (0x084UL << 32)
#define _SUB_DSZ16 (0x085UL << 32)
#define _XOR_DSZ16 (0x086UL << 32)
#define _NOTAND_DSZ16 (0x087UL << 32)
#define _ZEROEXT_DSZ16 (0x088UL << 32)
/* #define _SAVEUIP (0x08cUL << 32) */
#define _BT_DSZ16 (0x094UL << 32)
#define _BTS_DSZ16 (0x095UL << 32)
#define _BTR_DSZ16 (0x096UL << 32)
#define _BTC_DSZ16 (0x097UL << 32)
#define _CONCAT_DSZ16 (0x0a1UL << 32)
#define _SHL_DSZ16 (0x0a4UL << 32)
#define _SHR_DSZ16 (0x0a5UL << 32)
#define _MOVSX_DSZ16 (0x0a8UL << 32)
#define _MOVZX_DSZ16 (0x0a9UL << 32)
#define _ROL_DSZ16 (0x0acUL << 32)
#define _ROR_DSZ16 (0x0adUL << 32)
#define _SAR_DSZ16 (0x0aeUL << 32)
#define _CMOVCC_DSZ16_CONDO (0x0b4UL << 32)
#define _CMOVCC_DSZ16_CONDNO (0x0b5UL << 32)
#define _CMOVCC_DSZ16_CONDB (0x0b6UL << 32)
#define _CMOVCC_DSZ16_CONDNB (0x0b7UL << 32)
#define _ADD_DSZ8 (0x0c0UL << 32)
#define _OR_DSZ8 (0x0c1UL << 32)
#define _AND_DSZ8 (0x0c4UL << 32)
#define _SUB_DSZ8 (0x0c5UL << 32)
#define _XOR_DSZ8 (0x0c6UL << 32)
#define _NOTAND_DSZ8 (0x0c7UL << 32)
#define _ZEROEXT_DSZ8 (0x0c8UL << 32)
/* #define _SAVEUIP (0x0ccUL << 32) */
#define _NEG_DSZ8 (0x0e0UL << 32)
#define _CONCAT_DSZ8 (0x0e1UL << 32)
#define _SHL_DSZ8 (0x0e4UL << 32)
#define _SHR_DSZ8 (0x0e5UL << 32)
#define _MOVSX_DSZ8 (0x0e8UL << 32)
#define _MOVZX_DSZ8 (0x0e9UL << 32)
#define _ROL_DSZ8 (0x0ecUL << 32)
#define _ROR_DSZ8 (0x0edUL << 32)
#define _SAR_DSZ8 (0x0eeUL << 32)
#define _CMOVCC_DSZ8_CONDO (0x0f4UL << 32)
#define _CMOVCC_DSZ8_CONDNO (0x0f5UL << 32)
#define _CMOVCC_DSZ8_CONDB (0x0f6UL << 32)
#define _CMOVCC_DSZ8_CONDNB (0x0f7UL << 32)
#define _SETCC_CONDO (0x0f8UL << 32)
#define _SETCC_CONDNO (0x0f9UL << 32)
#define _SETCC_CONDB (0x0faUL << 32)
#define _SETCC_CONDNB (0x0fbUL << 32)
#define _READUIP_REGOVR (0x108UL << 32)
#define _SUBR_DSZ32 (0x120UL << 32)
#define _RCXBTCNTMSK_DSZ32 (0x122UL << 32)
#define _SELECTCC_DSZ32_CONDZ (0x130UL << 32)
#define _SELECTCC_DSZ32_CONDNZ (0x131UL << 32)
#define _SELECTCC_DSZ32_CONDBE (0x132UL << 32)
#define _SELECTCC_DSZ32_CONDNBE (0x133UL << 32)
#define _CMOVCC_DSZ32_CONDZ (0x134UL << 32)
#define _CMOVCC_DSZ32_CONDNZ (0x135UL << 32)
#define _CMOVCC_DSZ32_CONDBE (0x136UL << 32)
#define _CMOVCC_DSZ32_CONDNBE (0x137UL << 32)
#define _MOVEMERGEFLGS_DSZ32 (0x13eUL << 32)
#define _UFLOWCTRL (0x142UL << 32)
#define _AETTRACE (0x143UL << 32)
#define _URET (0x148UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDZ (0x150UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNZ (0x151UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDBE (0x152UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNBE (0x153UL << 32)
#define _MJMPCC_DSZNOP_CONDZ (0x158UL << 32)
#define _MJMPCC_DSZNOP_CONDNZ (0x159UL << 32)
#define _MJMPCC_DSZNOP_CONDBE (0x15aUL << 32)
#define _MJMPCC_DSZNOP_CONDNBE (0x15bUL << 32)
#define _UJMP (0x15dUL << 32)
#define _UJMPCC_DIRECT_TAKEN_CONDZ (0x15fUL << 32)
#define _SUBR_DSZ64 (0x160UL << 32)
#define _RCXBTCNTMSK_DSZ64 (0x162UL << 32)
#define _SELECTCC_DSZ64_CONDZ (0x170UL << 32)
#define _SELECTCC_DSZ64_CONDNZ (0x171UL << 32)
#define _SELECTCC_DSZ64_CONDBE (0x172UL << 32)
#define _SELECTCC_DSZ64_CONDNBE (0x173UL << 32)
#define _CMOVCC_DSZ64_CONDZ (0x174UL << 32)
#define _CMOVCC_DSZ64_CONDNZ (0x175UL << 32)
#define _CMOVCC_DSZ64_CONDBE (0x176UL << 32)
#define _CMOVCC_DSZ64_CONDNBE (0x177UL << 32)
#define _MOVEMERGEFLGS_DSZ64 (0x17eUL << 32)
#define _ADDSUB_DSZ16_CONDD (0x189UL << 32)
#define _SUBR_DSZ16 (0x1a0UL << 32)
#define _RCXBTCNTMSK_DSZ16 (0x1a2UL << 32)
#define _CMOVCC_DSZ16_CONDZ (0x1b4UL << 32)
#define _CMOVCC_DSZ16_CONDNZ (0x1b5UL << 32)
#define _CMOVCC_DSZ16_CONDBE (0x1b6UL << 32)
#define _CMOVCC_DSZ16_CONDNBE (0x1b7UL << 32)
#define _SAHF (0x1bfUL << 32)
#define _SUBR_DSZ8 (0x1e0UL << 32)
#define _RCXBTCNTMSK_DSZ8 (0x1e2UL << 32)
#define _CMOVCC_DSZ8_CONDZ (0x1f4UL << 32)
#define _CMOVCC_DSZ8_CONDNZ (0x1f5UL << 32)
#define _CMOVCC_DSZ8_CONDBE (0x1f6UL << 32)
#define _CMOVCC_DSZ8_CONDNBE (0x1f7UL << 32)
#define _SETCC_CONDZ (0x1f8UL << 32)
#define _SETCC_CONDNZ (0x1f9UL << 32)
#define _SETCC_CONDBE (0x1faUL << 32)
#define _SETCC_CONDNBE (0x1fbUL << 32)
#define _PSELECT_CPL0 (0x202UL << 32)
#define _FETCHFROMEIP0_ASZ32 (0x214UL << 32)
#define _FETCHFROMEIP1_ASZ32 (0x215UL << 32)
#define _SIGEVENT (0x21eUL << 32)
#define _IMUL32L_DSZ32 (0x225UL << 32)
#define _MSR2CR (0x228UL << 32)
#define _MUL_DSZ32 (0x22cUL << 32)
#define _IMUL_DSZ32 (0x22dUL << 32)
#define _SELECTCC_DSZ32_CONDS (0x230UL << 32)
#define _SELECTCC_DSZ32_CONDNS (0x231UL << 32)
#define _SELECTCC_DSZ32_CONDP (0x232UL << 32)
#define _SELECTCC_DSZ32_CONDNP (0x233UL << 32)
#define _CMOVCC_DSZ32_CONDS (0x234UL << 32)
#define _CMOVCC_DSZ32_CONDNS (0x235UL << 32)
#define _CMOVCC_DSZ32_CONDP (0x236UL << 32)
#define _CMOVCC_DSZ32_CONDNP (0x237UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDS (0x250UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNS (0x251UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDP (0x252UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNP (0x253UL << 32)
#define _FETCHFROMEIP0_ASZ64 (0x254UL << 32)
#define _FETCHFROMEIP1_ASZ64 (0x255UL << 32)
#define _MJMPCC_DSZNOP_CONDS (0x258UL << 32)
#define _MJMPCC_DSZNOP_CONDNS (0x259UL << 32)
#define _MJMPCC_DSZNOP_CONDP (0x25aUL << 32)
#define _MJMPCC_DSZNOP_CONDNP (0x25bUL << 32)
#define _TEST_DSZ64 (0x25dUL << 32)
#define _IMUL64L_DSZ64 (0x264UL << 32)
#define _RDVMCSPLA (0x269UL << 32)
#define _SELECTCC_DSZ64_CONDS (0x270UL << 32)
#define _SELECTCC_DSZ64_CONDNS (0x271UL << 32)
#define _SELECTCC_DSZ64_CONDP (0x272UL << 32)
#define _SELECTCC_DSZ64_CONDNP (0x273UL << 32)
#define _CMOVCC_DSZ64_CONDS (0x274UL << 32)
#define _CMOVCC_DSZ64_CONDNS (0x275UL << 32)
#define _CMOVCC_DSZ64_CONDP (0x276UL << 32)
#define _CMOVCC_DSZ64_CONDNP (0x277UL << 32)
#define _CMOVCC_DSZ16_CONDS (0x2b4UL << 32)
#define _CMOVCC_DSZ16_CONDNS (0x2b5UL << 32)
#define _CMOVCC_DSZ16_CONDP (0x2b6UL << 32)
#define _CMOVCC_DSZ16_CONDNP (0x2b7UL << 32)
#define _CMOVCC_DSZ8_CONDS (0x2f4UL << 32)
#define _CMOVCC_DSZ8_CONDNS (0x2f5UL << 32)
#define _CMOVCC_DSZ8_CONDP (0x2f6UL << 32)
#define _CMOVCC_DSZ8_CONDNP (0x2f7UL << 32)
#define _SETCC_CONDS (0x2f8UL << 32)
#define _SETCC_CONDNS (0x2f9UL << 32)
#define _SETCC_CONDP (0x2faUL << 32)
#define _SETCC_CONDNP (0x2fbUL << 32)
#define _RCL_DSZ32 (0x32eUL << 32)
#define _SELECTCC_DSZ32_CONDL (0x330UL << 32)
#define _SELECTCC_DSZ32_CONDNL (0x331UL << 32)
#define _SELECTCC_DSZ32_CONDLE (0x332UL << 32)
#define _SELECTCC_DSZ32_CONDNLE (0x333UL << 32)
#define _CMOVCC_DSZ32_CONDL (0x334UL << 32)
#define _CMOVCC_DSZ32_CONDNL (0x335UL << 32)
#define _CMOVCC_DSZ32_CONDLE (0x336UL << 32)
#define _CMOVCC_DSZ32_CONDNLE (0x337UL << 32)
#define _CLC (0x338UL << 32)
#define _CMC (0x339UL << 32)
#define _STC (0x33aUL << 32)
#define _BSWAP_DSZ32 (0x33cUL << 32)
#define _ADC (0x33eUL << 32)
#define _SBB (0x33fUL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDL (0x350UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNL (0x351UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDLE (0x352UL << 32)
#define _UJMPCC_DIRECT_NOTTAKEN_CONDNLE (0x353UL << 32)
#define _MJMPCC_DSZNOP_CONDL (0x358UL << 32)
#define _MJMPCC_DSZNOP_CONDNL (0x359UL << 32)
#define _MJMPCC_DSZNOP_CONDLE (0x35aUL << 32)
#define _MJMPCC_DSZNOP_CONDNLE (0x35bUL << 32)
#define _SELECTCC_DSZ64_CONDL (0x370UL << 32)
#define _SELECTCC_DSZ64_CONDNL (0x371UL << 32)
#define _SELECTCC_DSZ64_CONDLE (0x372UL << 32)
#define _SELECTCC_DSZ64_CONDNLE (0x373UL << 32)
#define _CMOVCC_DSZ64_CONDL (0x374UL << 32)
#define _CMOVCC_DSZ64_CONDNL (0x375UL << 32)
#define _CMOVCC_DSZ64_CONDLE (0x376UL << 32)
#define _CMOVCC_DSZ64_CONDNLE (0x377UL << 32)
#define _GENARITHFLAGS (0x37dUL << 32)
#define _READAFLAGS (0x380UL << 32)
#define _RCL_DSZ16 (0x3aeUL << 32)
#define _CMOVCC_DSZ16_CONDL (0x3b4UL << 32)
#define _CMOVCC_DSZ16_CONDNL (0x3b5UL << 32)
#define _CMOVCC_DSZ16_CONDLE (0x3b6UL << 32)
#define _CMOVCC_DSZ16_CONDNLE (0x3b7UL << 32)
#define _LAHF (0x3c0UL << 32)
#define _INC_DSZ8 (0x3c8UL << 32)
#define _DEC_DSZ8 (0x3caUL << 32)
#define _RCL_DSZ8 (0x3eeUL << 32)
#define _CMOVCC_DSZ8_CONDL (0x3f4UL << 32)
#define _CMOVCC_DSZ8_CONDNL (0x3f5UL << 32)
#define _CMOVCC_DSZ8_CONDLE (0x3f6UL << 32)
#define _CMOVCC_DSZ8_CONDNLE (0x3f7UL << 32)
#define _SETCC_CONDL (0x3f8UL << 32)
#define _SETCC_CONDNL (0x3f9UL << 32)
#define _SETCC_CONDLE (0x3faUL << 32)
#define _SETCC_CONDNLE (0x3fbUL << 32)
/* #define _ADC (0x3feUL << 32) */
/* #define _SBB (0x3ffUL << 32) */
#define _PSUBSB (0x440UL << 32)
#define _PSUBSW (0x441UL << 32)
#define _PMINSW (0x442UL << 32)
#define _POR (0x443UL << 32)
#define _PADDSB (0x444UL << 32)
#define _PADDSW (0x445UL << 32)
#define _PMAXSW (0x446UL << 32)
#define _PXOR (0x447UL << 32)
#define _PSUBB (0x448UL << 32)
#define _PSUBW (0x449UL << 32)
#define _PSUBD (0x44aUL << 32)
#define _PADDB (0x44cUL << 32)
#define _PADDW (0x44dUL << 32)
#define _PADDD (0x44eUL << 32)
#define _PCMPGTB (0x450UL << 32)
#define _PCMPGTW (0x451UL << 32)
#define _PCMPGTD (0x452UL << 32)
#define _PALIGNR (0x457UL << 32)
#define _PCMPEQW (0x458UL << 32)
#define _PCMPEQB (0x459UL << 32)
#define _PCMPEQD (0x45aUL << 32)
#define _PADDQ (0x45bUL << 32)
#define _PSUBQ (0x45fUL << 32)
#define _PSUBUSB (0x460UL << 32)
#define _PSUBUSW (0x461UL << 32)
#define _PMINUB (0x462UL << 32)
#define _PAND (0x463UL << 32)
#define _PADDUSB (0x464UL << 32)
#define _PADDUSW (0x465UL << 32)
#define _PMAXUB (0x466UL << 32)
#define _PANDN (0x467UL << 32)
#define _PAVGB (0x468UL << 32)
#define _PAVGW (0x46bUL << 32)
#define _MOVLPD (0x470UL << 32)
#define _MOVHPD (0x471UL << 32)
#define _MOVDQU (0x472UL << 32)
#define _FMOV (0x4b4UL << 32)
#define _ORPD (0x4c3UL << 32)
#define _XORPD (0x4c7UL << 32)
#define _ANDPD (0x4e3UL << 32)
#define _ANDNPD (0x4e7UL << 32)
#define _MOVHLPS (0x4efUL << 32)
#define _PUNPCKLDQ (0x508UL << 32)
#define _PSRLQ (0x50aUL << 32)
#define _PSLLQ (0x50eUL << 32)
#define _CVTPD2PI (0x514UL << 32)
#define _PUNPCKHDQ (0x518UL << 32)
/* #define _PSRLQ (0x51aUL << 32) */
#define _PACKSSDW (0x51dUL << 32)
/* #define _PSLLQ (0x51eUL << 32) */
#define _UNPCKHPD (0x528UL << 32)
#define _UNPCKLPD (0x529UL << 32)
#define _PMADDWD (0x556UL << 32)
#define _PSADBW (0x557UL << 32)
#define _CVTPD2PS (0x571UL << 32)
#define _PUNPCKLWD (0x588UL << 32)
#define _PSRLD (0x58aUL << 32)
#define _PSRAD (0x58cUL << 32)
#define _PSLLD (0x58eUL << 32)
#define _CVTTPD2PI (0x594UL << 32)
#define _PUNPCKHWD (0x598UL << 32)
/* #define _PSRLD (0x59aUL << 32) */
#define _PSHUFD (0x59bUL << 32)
/* #define _PSRAD (0x59cUL << 32) */
#define _PACKSSWB (0x59dUL << 32)
/* #define _PSLLD (0x59eUL << 32) */
#define _PACKUSWB (0x59fUL << 32)
#define _PUNPCKLBW (0x5c8UL << 32)
#define _PSRLW (0x5caUL << 32)
#define _PSRAW (0x5ccUL << 32)
#define _PSLLW (0x5ceUL << 32)
#define _PUNPCKHBW (0x5d8UL << 32)
/* #define _PSRLW (0x5daUL << 32) */
/* #define _PSRAW (0x5dcUL << 32) */
/* #define _PSLLW (0x5deUL << 32) */
#define _CVTDQ2PS (0x5f3UL << 32)
#define _CVTPI2PD (0x5f5UL << 32)
#define _MOVUSS (0x539UL << 32)
#define _SHUFSS (0x53aUL << 32)
#define _MOVUSD (0x579UL << 32)
#define _SHUFSD (0x57aUL << 32)
#define _MOVUPD (0x5b9UL << 32)
#define _SHUFPD (0x5baUL << 32)
#define _MOVUPS (0x5f9UL << 32)
#define _SHUFPS (0x5faUL << 32)
#define _FADDP (0x608UL << 32)
#define _FDIV (0x646UL << 32)
#define _PMULUDQ (0x650UL << 32)
#define _PMULHUW (0x652UL << 32)
#define _PMULLW (0x654UL << 32)
#define _PMULHW (0x655UL << 32)
#define _FILD (0x685UL << 32)
#define _FCOM2 (0x68aUL << 32)
#define _MULSS (0x631UL << 32)
#define _SQRTSS (0x635UL << 32)
#define _DIVSS (0x636UL << 32)
#define _ADDSS (0x638UL << 32)
#define _SUBSS (0x63cUL << 32)
#define _MINSS (0x63dUL << 32)
#define _CMPSS (0x63eUL << 32)
#define _MAXSS (0x63fUL << 32)
#define _SQRTSD (0x675UL << 32)
#define _DIVSD (0x676UL << 32)
#define _ADDSD (0x678UL << 32)
#define _SUBSD (0x67cUL << 32)
#define _MINSD (0x67dUL << 32)
#define _CMPSD (0x67eUL << 32)
#define _MAXSD (0x67fUL << 32)
#define _MULPD (0x6b1UL << 32)
#define _SQRTPD (0x6b5UL << 32)
#define _DIVPD (0x6b6UL << 32)
#define _ADDPD (0x6b8UL << 32)
#define _SUBPD (0x6bcUL << 32)
#define _MINPD (0x6bdUL << 32)
#define _CMPPD (0x6beUL << 32)
#define _MAXPD (0x6bfUL << 32)
#define _MULPS (0x6f1UL << 32)
#define _SQRTPS (0x6f5UL << 32)
#define _DIVPS (0x6f6UL << 32)
#define _ADDPS (0x6f8UL << 32)
#define _SUBPS (0x6fcUL << 32)
#define _MINPS (0x6fdUL << 32)
#define _CMPPS (0x6feUL << 32)
#define _MAXPS (0x6ffUL << 32)
#define _PINTMOVDI2MM_DSZ32 (0x705UL << 32)
#define _FPREADROM_DTYPENOP (0x716UL << 32)
#define _FCOMIP (0x720UL << 32)
#define _COMISD (0x722UL << 32)
#define _UCOMISD (0x723UL << 32)
#define _PINTMOVDTMM2I_DSZ32 (0x72cUL << 32)
#define _PINTMOVDMM2I_DSZ32 (0x72dUL << 32)
#define _PINTMOVDI2MM_DSZ64 (0x745UL << 32)
#define _PMOVMSKB (0x769UL << 32)
#define _PINTMOVDTMM2I_DSZ64 (0x76cUL << 32)
#define _PINTMOVDMM2I_DSZ64 (0x76dUL << 32)
#define _PINSRW (0x785UL << 32)
#define _PEXTRW (0x7adUL << 32)
#define _RSQRTPS (0x7b8UL << 32)
#define _FCMOVNE (0x7edUL << 32)
#define _MOVMSKPD (0x7f8UL << 32)
#define _LA2LIN_DSZ32 (0x81fUL << 32)
#define _MOVETOCREG_AND_DSZ64 (0x822UL << 32)
#define _BTUJB_DIRECT_NOTTAKEN (0x86aUL << 32)
#define _BTUJNB_DIRECT_NOTTAKEN (0x86bUL << 32)
#define _LA2LIN_DSZ64 (0x89fUL << 32)
#define _MOVETOCREG_SHL_DSZ64 (0x8a2UL << 32)
#define _MOVETOCREG_OR_DSZ64 (0x902UL << 32)
#define _CMPUJZ_DIRECT_NOTTAKEN (0x928UL << 32)
#define _CMPUJNZ_DIRECT_NOTTAKEN (0x929UL << 32)
#define _MOVETOCREG_BTS_DSZ64 (0x962UL << 32)
#define _MOVETOCREG_SHR_DSZ64 (0x9a2UL << 32)
#define _SHLD (0x996UL << 32)
#define _SHRD (0x997UL << 32)
#define _MOVETOCREG_BTR_DSZ64 (0xa62UL << 32)
#define _LDZX_DSZ32_ASZ32_SC1 (0xc00UL << 32)
#define _LEA_DSZ32_ASZ32_SC1 (0xc03UL << 32)
#define _STAD_DSZ32_ASZ32_SC1 (0xc08UL << 32)
#define _STADTICKLE_DSZ32_ASZ32_SC1 (0xc09UL << 32)
#define _LDTICKLE_DSZ32_ASZ32_SC1 (0xc0aUL << 32)
#define _MOVNTPD (0xc0eUL << 32)
/* #define _LDZX_DSZ32_ASZ32_SC1 (0xc10UL << 32) */
/* #define _LEA_DSZ32_ASZ32_SC1 (0xc13UL << 32) */
/* #define _STAD_DSZ32_ASZ32_SC1 (0xc18UL << 32) */
/* #define _STADTICKLE_DSZ32_ASZ32_SC1 (0xc19UL << 32) */
/* #define _LDTICKLE_DSZ32_ASZ32_SC1 (0xc1aUL << 32) */
/* #define _MOVHPD (0xc2eUL << 32) */
/* #define _LDZX_DSZ32_ASZ32_SC1 (0xc30UL << 32) */
/* #define _LEA_DSZ32_ASZ32_SC1 (0xc33UL << 32) */
/* #define _STAD_DSZ32_ASZ32_SC1 (0xc38UL << 32) */
/* #define _STADTICKLE_DSZ32_ASZ32_SC1 (0xc39UL << 32) */
/* #define _LDTICKLE_DSZ32_ASZ32_SC1 (0xc3aUL << 32) */
#define _LDZX_DSZ64_ASZ32_SC1 (0xc40UL << 32)
#define _LEA_DSZ64_ASZ32_SC1 (0xc43UL << 32)
#define _STAD_DSZ64_ASZ32_SC1 (0xc48UL << 32)
#define _STADTICKLE_DSZ64_ASZ32_SC1 (0xc49UL << 32)
#define _LDTICKLE_DSZ64_ASZ32_SC1 (0xc4aUL << 32)
#define _RDSEGFLD (0xc4bUL << 32)
/* #define _LDZX_DSZ64_ASZ32_SC1 (0xc50UL << 32) */
/* #define _LEA_DSZ64_ASZ32_SC1 (0xc53UL << 32) */
/* #define _STAD_DSZ64_ASZ32_SC1 (0xc58UL << 32) */
/* #define _STADTICKLE_DSZ64_ASZ32_SC1 (0xc59UL << 32) */
/* #define _LDTICKLE_DSZ64_ASZ32_SC1 (0xc5aUL << 32) */
/* #define _MOVLPD (0xc5eUL << 32) */
#define _WRSEGFLD (0xc6bUL << 32)
#define _STAD_DSZ64_ASZ64_SC1 (0xc68UL << 32)
/* #define _LDZX_DSZ64_ASZ32_SC1 (0xc70UL << 32) */
/* #define _LEA_DSZ64_ASZ32_SC1 (0xc73UL << 32) */
/* #define _STAD_DSZ64_ASZ64_SC8 (0xc78UL << 32) */
/* #define _STADTICKLE_DSZ64_ASZ32_SC1 (0xc79UL << 32) */
/* #define _LDTICKLE_DSZ64_ASZ32_SC1 (0xc7aUL << 32) */
/* #define _WRSEGFLD (0xc7bUL << 32) */
/* #define _LDZX_DSZ16_ASZ32_SC1 (0xc80UL << 32) */
#define _LEA_DSZ16_ASZ32_SC1 (0xc83UL << 32)
#define _STAD_DSZ16_ASZ32_SC1 (0xc88UL << 32)
#define _STADTICKLE_DSZ16_ASZ32_SC1 (0xc89UL << 32)
#define _LDTICKLE_DSZ16_ASZ32_SC1 (0xc8aUL << 32)
/* #define _LDZX_DSZ16_ASZ32_SC1 (0xc90UL << 32) */
/* #define _LEA_DSZ16_ASZ32_SC1 (0xc93UL << 32) */
/* #define _STAD_DSZ16_ASZ32_SC1 (0xc98UL << 32) */
/* #define _STADTICKLE_DSZ16_ASZ32_SC1 (0xc99UL << 32) */
/* #define _LDTICKLE_DSZ16_ASZ32_SC1 (0xc9aUL << 32) */
#define _LDZX_DSZ16_ASZ32_SC1 (0xcb0UL << 32)
/* #define _LEA_DSZ16_ASZ32_SC1 (0xcb3UL << 32) */
/* #define _STAD_DSZ16_ASZ32_SC1 (0xcb8UL << 32) */
/* #define _STADTICKLE_DSZ16_ASZ32_SC1 (0xcb9UL << 32) */
/* #define _LDTICKLE_DSZ16_ASZ32_SC1 (0xcbaUL << 32) */
#define _MOVNTDQ (0xcbeUL << 32)
#define _LDZX_DSZ8_ASZ32_SC1 (0xcc0UL << 32)
#define _LEA_DSZ8_ASZ32_SC1 (0xccfUL << 32)
#define _STAD_DSZ8_ASZ32_SC1 (0xcc8UL << 32)
#define _STADTICKLE_DSZ8_ASZ32_SC1 (0xcc9UL << 32)
#define _LDTICKLE_DSZ8_ASZ32_SC1 (0xccaUL << 32)
/* #define _LDZX_DSZ8_ASZ32_SC1 (0xcd0UL << 32) */
/* #define _LEA_DSZ8_ASZ32_SC1 (0xcd3UL << 32) */
/* #define _STAD_DSZ8_ASZ32_SC1 (0xcd8UL << 32) */
/* #define _STADTICKLE_DSZ8_ASZ32_SC1 (0xcd9UL << 32) */
/* #define _LDTICKLE_DSZ8_ASZ32_SC1 (0xcdaUL << 32) */
#define _STAD_DSZ8_ASZ64_SC1 (0xce8UL << 32)
/* #define _LDZX_DSZ8_ASZ32_SC1 (0xcf0UL << 32) */
/* #define _LEA_DSZ8_ASZ32_SC1 (0xcf3UL << 32) */
#define _LDHINT_BUFFER_ASZ32_SC1 (0xcf5UL << 32)
/* #define _STAD_DSZ8_ASZ32_SC1 (0xcf8UL << 32) */
/* #define _STADTICKLE_DSZ8_ASZ32_SC1 (0xcf9UL << 32) */
/* #define _LDTICKLE_DSZ8_ASZ32_SC1 (0xcfaUL << 32) */
#define _MASKMOVDQU (0xcfeUL << 32)
#define _LDZX_DSZ32_ASZ32_SC4 (0xd00UL << 32)
#define _LEA_DSZ32_ASZ32_SC4 (0xd03UL << 32)
#define _STAD_DSZ32_ASZ32_SC4 (0xd08UL << 32)
#define _STADTICKLE_DSZ32_ASZ32_SC4 (0xd09UL << 32)
#define _LDTICKLE_DSZ32_ASZ32_SC4 (0xd0aUL << 32)
#define _PORTIN_DSZ32_ASZ16_SC1 (0xd0bUL << 32)
#define _PORTOUT_DSZ32_ASZ16_SC1 (0xd0fUL << 32)
/* #define _LDZX_DSZ32_ASZ32_SC4 (0xd10UL << 32) */
/* #define _LEA_DSZ32_ASZ32_SC4 (0xd13UL << 32) */
/* #define _STAD_DSZ32_ASZ32_SC4 (0xd18UL << 32) */
/* #define _STADTICKLE_DSZ32_ASZ32_SC4 (0xd19UL << 32) */
/* #define _LDTICKLE_DSZ32_ASZ32_SC4 (0xd1aUL << 32) */
/* #define _LDZX_DSZ32_ASZ32_SC1 (0xd30UL << 32) */
/* #define _LEA_DSZ32_ASZ32_SC1 (0xd33UL << 32) */
/* #define _STAD_DSZ32_ASZ32_SC1 (0xd38UL << 32) */
/* #define _STADTICKLE_DSZ32_ASZ32_SC1 (0xd39UL << 32) */
/* #define _LDTICKLE_DSZ32_ASZ32_SC1 (0xd3aUL << 32) */
#define _LDZX_DSZ64_ASZ32_SC4 (0xd40UL << 32)
#define _LEA_DSZ64_ASZ32_SC4 (0xd43UL << 32)
#define _STAD_DSZ64_ASZ32_SC4 (0xd48UL << 32)
#define _STADTICKLE_DSZ64_ASZ32_SC4 (0xd49UL << 32)
#define _LDTICKLE_DSZ64_ASZ32_SC4 (0xd4aUL << 32)
#define _PORTIN_DSZ64_ASZ16_SC1 (0xd4bUL << 32)
#define _PORTOUT_DSZ64_ASZ16_SC1 (0xd4fUL << 32)
/* #define _LDZX_DSZ64_ASZ32_SC4 (0xd50UL << 32) */
/* #define _LEA_DSZ64_ASZ32_SC4 (0xd53UL << 32) */
/* #define _STAD_DSZ64_ASZ32_SC4 (0xd58UL << 32) */
/* #define _STADTICKLE_DSZ64_ASZ32_SC4 (0xd59UL << 32) */
/* #define _LDTICKLE_DSZ64_ASZ32_SC4 (0xd5aUL << 32) */
/* #define _LDZX_DSZ64_ASZ32_SC1 (0xd70UL << 32) */
/* #define _LEA_DSZ64_ASZ32_SC1 (0xd73UL << 32) */
#define _STAD_DSZ64_ASZ32_SC8 (0xd78UL << 32)
/* #define _STADTICKLE_DSZ64_ASZ32_SC1 (0xd79UL << 32) */
/* #define _LDTICKLE_DSZ64_ASZ32_SC1 (0xd7aUL << 32) */
#define _LDZX_DSZ16_ASZ32_SC4 (0xd80UL << 32)
#define _LEA_DSZ16_ASZ32_SC4 (0xd83UL << 32)
#define _STAD_DSZ16_ASZ32_SC4 (0xd88UL << 32)
#define _STADTICKLE_DSZ16_ASZ32_SC4 (0xd89UL << 32)
#define _LDTICKLE_DSZ16_ASZ32_SC4 (0xd8aUL << 32)
#define _PORTIN_DSZ16_ASZ16_SC1 (0xd8bUL << 32)
#define _PORTOUT_DSZ16_ASZ16_SC1 (0xd8fUL << 32)
/* #define _LDZX_DSZ16_ASZ32_SC4 (0xd90UL << 32) */
/* #define _LEA_DSZ16_ASZ32_SC4 (0xd93UL << 32) */
/* #define _STAD_DSZ16_ASZ32_SC4 (0xd98UL << 32) */
/* #define _STADTICKLE_DSZ16_ASZ32_SC4 (0xd99UL << 32) */
/* #define _LDTICKLE_DSZ16_ASZ32_SC4 (0xd9aUL << 32) */
/* #define _LDZX_DSZ16_ASZ32_SC1 (0xdb0UL << 32) */
/* #define _LEA_DSZ16_ASZ32_SC1 (0xdb3UL << 32) */
/* #define _STAD_DSZ16_ASZ32_SC1 (0xdb8UL << 32) */
/* #define _STADTICKLE_DSZ16_ASZ32_SC1 (0xdb9UL << 32) */
/* #define _LDTICKLE_DSZ16_ASZ32_SC1 (0xdbaUL << 32) */
#define _LDZX_DSZ8_ASZ32_SC4 (0xdc0UL << 32)
#define _LEA_DSZ8_ASZ32_SC4 (0xdc3UL << 32)
#define _STAD_DSZ8_ASZ32_SC4 (0xdc8UL << 32)
#define _STADTICKLE_DSZ8_ASZ32_SC4 (0xdc9UL << 32)
#define _LDTICKLE_DSZ8_ASZ32_SC4 (0xdcaUL << 32)
#define _PORTIN_DSZ8_ASZ16_SC1 (0xdcbUL << 32)
#define _PORTOUT_DSZ8_ASZ16_SC1 (0xdcfUL << 32)
/* #define _LDZX_DSZ8_ASZ32_SC4 (0xdd0UL << 32) */
/* #define _LEA_DSZ8_ASZ32_SC4 (0xdd3UL << 32) */
/* #define _STAD_DSZ8_ASZ32_SC4 (0xdd8UL << 32) */
/* #define _STADTICKLE_DSZ8_ASZ32_SC4 (0xdd9UL << 32) */
/* #define _LDTICKLE_DSZ8_ASZ32_SC4 (0xddaUL << 32) */
/* #define _LDZX_DSZ8_ASZ32_SC1 (0xdf0UL << 32) */
/* #define _LEA_DSZ8_ASZ32_SC1 (0xdf3UL << 32) */
/* #define _STAD_DSZ8_ASZ32_SC1 (0xdf8UL << 32) */
/* #define _STADTICKLE_DSZ8_ASZ32_SC1 (0xdf9UL << 32) */
/* #define _LDTICKLE_DSZ8_ASZ32_SC1 (0xdfaUL << 32) */
#define _LDPPHYS_DSZ32_ASZ16_SC1 (0xe00UL << 32)
#define _STADPPHYS_DSZ32_ASZ16_SC1 (0xe08UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ16_SC1 (0xe0aUL << 32) */
#define _STADPPHYSTICKLE_DSZ32_ASZ16_SC1 (0xe0dUL << 32)
#define _LDPPHYS_DSZ32_ASZ64_SC1 (0xe20UL << 32)
#define _LDPPHYSTICKLE_DSZ32_ASZ64_SC1 (0xe25UL << 32)
#define _STADPPHYS_DSZ32_ASZ64_SC1 (0xe28UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ64_SC1 (0xe2aUL << 32) */
#define _STADPPHYSTICKLE_DSZ32_ASZ64_SC1 (0xe2dUL << 32)
#define _SIMDSTADPPHYS_DSZ32_ASZ64_SC1 (0xe2eUL << 32)
#define _LDPPHYS_DSZ32_ASZ64_SC8 (0xe30UL << 32)
#define _STADPPHYS_DSZ32_ASZ64_SC8 (0xe38UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ64_SC8 (0xe3aUL << 32) */
#define _LDPPHYS_DSZ64_ASZ16_SC1 (0xe40UL << 32)
#define _STADPPHYS_DSZ64_ASZ16_SC1 (0xe48UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ16_SC1 (0xe4aUL << 32) */
#define _STADPPHYSTICKLE_DSZ64_ASZ16_SC1 (0xe4dUL << 32)
#define _LDPPHYS_DSZ64_ASZ64_SC1 (0xe60UL << 32)
#define _LDPPHYSTICKLE_DSZ64_ASZ64_SC1 (0xe65UL << 32)
#define _STADPPHYS_DSZ64_ASZ64_SC1 (0xe68UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ64_SC1 (0xe6aUL << 32) */
#define _STADPPHYSTICKLE_DSZ64_ASZ64_SC1 (0xe6dUL << 32)
#define _SIMDSTADPPHYS_DSZ64_ASZ64_SC1 (0xe6eUL << 32)
#define _LDPPHYS_DSZ64_ASZ64_SC8 (0xe70UL << 32)
#define _LDSTGBUF_DSZ64_ASZ16_SC1 (0xe75UL << 32)
#define _STADPPHYS_DSZ64_ASZ64_SC8 (0xe78UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ64_SC8 (0xe7aUL << 32) */
#define _STADSTGBUF_DSZ64_ASZ16_SC1 (0xe7dUL << 32)
#define _LDPPHYS_DSZ16_ASZ16_SC1 (0xe80UL << 32)
#define _STADPPHYS_DSZ16_ASZ16_SC1 (0xe88UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ16_SC1 (0xe8aUL << 32) */
#define _STADPPHYSTICKLE_DSZ16_ASZ16_SC1 (0xe8dUL << 32)
#define _LDPPHYS_DSZ16_ASZ64_SC1 (0xea0UL << 32)
#define _LDPPHYSTICKLE_DSZ16_ASZ64_SC1 (0xea5UL << 32)
#define _STADPPHYS_DSZ16_ASZ64_SC1 (0xea8UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ64_SC1 (0xeaaUL << 32) */
#define _STADPPHYSTICKLE_DSZ16_ASZ64_SC1 (0xeadUL << 32)
#define _SIMDLSTADSTGBUF_DSZ64_ASZ32_SC1 (0xeaeUL << 32)
#define _LDPPHYS_DSZ16_ASZ64_SC8 (0xeb0UL << 32)
#define _STADPPHYS_DSZ16_ASZ64_SC8 (0xeb8UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ64_SC8 (0xebaUL << 32) */
#define _LDPPHYS_DSZ8_ASZ16_SC1 (0xec0UL << 32)
#define _STADPPHYS_DSZ8_ASZ16_SC1 (0xec8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ16_SC1 (0xecaUL << 32) */
#define _LDHINT_CACHEALL_ASZ64_SC1 (0xecbUL << 32)
#define _STADPPHYSTICKLE_DSZ8_ASZ16_SC1 (0xecdUL << 32)
#define _LDHINT_CACHE1_ASZ64_SC1 (0xedbUL << 32)
#define _LDPPHYS_DSZ8_ASZ64_SC1 (0xee0UL << 32)
#define _LDPPHYSTICKLE_DSZ8_ASZ64_SC1 (0xee5UL << 32)
#define _STADPPHYS_DSZ8_ASZ64_SC1 (0xee8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ64_SC1 (0xeeaUL << 32) */
#define _LDHINT_CACHE2_ASZ64_SC1 (0xeebUL << 32)
#define _STADPPHYSTICKLE_DSZ8_ASZ64_SC1 (0xeedUL << 32)
#define _SIMDHSTADSTGBUF_DSZ64_ASZ32_SC1 (0xeeeUL << 32)
#define _LDPPHYS_DSZ8_ASZ64_SC8 (0xef0UL << 32)
#define _STADPPHYS_DSZ8_ASZ64_SC8 (0xef8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ64_SC8 (0xefaUL << 32) */
#define _LDPPHYS_DSZ32_ASZ32_SC4 (0xf00UL << 32)
#define _STADPPHYS_DSZ32_ASZ32_SC4 (0xf08UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ32_SC4 (0xf0aUL << 32) */
#define _LDPPHYS_DSZ32_ASZ32_SC1 (0xf20UL << 32)
#define _STADPPHYS_DSZ32_ASZ32_SC1 (0xf28UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ32_SC1 (0xf2aUL << 32) */
#define _LDPPHYS_DSZ32_ASZ32_SC8 (0xf30UL << 32)
#define _STADPPHYS_DSZ32_ASZ32_SC8 (0xf38UL << 32)
/* #define _LDPPHYS_DSZ32_ASZ32_SC8 (0xf3aUL << 32) */
#define _LDPPHYS_DSZ64_ASZ32_SC4 (0xf40UL << 32)
#define _STADPPHYS_DSZ64_ASZ32_SC4 (0xf48UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ32_SC4 (0xf4aUL << 32) */
#define _MPOP (0xf4bUL << 32)
#define _MPUSH (0xf4fUL << 32)
#define _LDPPHYS_DSZ64_ASZ32_SC1 (0xf60UL << 32)
#define _LDPPHYSTICKLE_DSZ64_ASZ32_SC1 (0xf65UL << 32)
#define _STADPPHYS_DSZ64_ASZ32_SC1 (0xf68UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ32_SC1 (0xf6aUL << 32) */
#define _MCALL_DIRECT (0xf6fUL << 32)
#define _LDPPHYS_DSZ64_ASZ32_SC8 (0xf70UL << 32)
#define _STADPPHYS_DSZ64_ASZ32_SC8 (0xf78UL << 32)
/* #define _LDPPHYS_DSZ64_ASZ32_SC8 (0xf7aUL << 32) */
#define _UCALLPARAM_INDIRECT (0xf7fUL << 32)
#define _LDPPHYS_DSZ16_ASZ32_SC4 (0xf80UL << 32)
#define _STADPPHYS_DSZ16_ASZ32_SC4 (0xf88UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ32_SC4 (0xf8aUL << 32) */
#define _LDPPHYS_DSZ16_ASZ32_SC1 (0xfa0UL << 32)
#define _STADPPHYS_DSZ16_ASZ32_SC1 (0xfa8UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ32_SC1 (0xfaaUL << 32) */
#define _LDPPHYS_DSZ16_ASZ32_SC8 (0xfb0UL << 32)
#define _STADPPHYS_DSZ16_ASZ32_SC8 (0xfb8UL << 32)
/* #define _LDPPHYS_DSZ16_ASZ32_SC8 (0xfbaUL << 32) */
#define _LDPPHYS_DSZ8_ASZ32_SC4 (0xfc0UL << 32)
#define _STADPPHYS_DSZ8_ASZ32_SC4 (0xfc8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ32_SC4 (0xfcaUL << 32) */
#define _LDPPHYS_DSZ8_ASZ32_SC1 (0xfe0UL << 32)
#define _STADPPHYS_DSZ8_ASZ32_SC1 (0xfe8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ32_SC1 (0xfeaUL << 32) */
#define _LBSYNC (0xfefUL << 32)
#define _LDPPHYS_DSZ8_ASZ32_SC8 (0xff0UL << 32)
#define _STADPPHYS_DSZ8_ASZ32_SC8 (0xff8UL << 32)
/* #define _LDPPHYS_DSZ8_ASZ32_SC8 (0xffaUL << 32) */
#define _SFENCE (0xfffUL << 32)

#define _PINTMOVQI2XMMHQ_DSZ64 (0x746UL << 32)
#define _PINTMOVQI2XMMLQ_DSZ64 (0x747UL << 32)
#define _PINTMOVQXMMLQ2I_DSZ64 (0x76fUL << 32)

#endif // OPCODE_H_
