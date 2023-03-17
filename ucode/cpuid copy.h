unsigned long addr = 0x7c10;
unsigned long hook_address = 0x0be0;
unsigned long ucode_patch[][4] = {
    {   // 0x7c10
        MOVE_DSZ64_IMM(TMP2, 0x8000), 
        SHL_DSZ64_IMM(TMP2, TMP2, 0x10), 
        OR_DSZ64_IMM(TMP2, TMP2, 0x0002), 
        NOP_SEQWORD 
    }, 
    {   // 0x7c14
        XOR_DSZ64_REG(TMP2, TMP2, RAX), 
        UJMPCC_DIRECT_NOTTAKEN_CONDZ(TMP2, 0x7c18), 
        MOVE_DSZ64_IMM(TMP0, 0xa), 
        SEQ_GOTO2(0x4808) 
    }, 
    {   // 0x7c18
        MOVE_DSZ64_IMM(RAX, 0x7473),
        CONCAT_DSZ16_IMM(RAX, RAX, 0x7563),
        NOP,
        NOP_SEQWORD 
    }, 
    {   // 0x7c1c
        MOVE_DSZ64_IMM(RBX, 0x632d),
        CONCAT_DSZ16_IMM(RBX, RBX, 0x6d6f),
        NOP,
        NOP_SEQWORD 
    }, 
    {   // 0x7c20
        MOVE_DSZ64_IMM(RCX, 0x6320),
        CONCAT_DSZ16_IMM(RCX, RCX, 0x7570),
        NOP,
        NOP_SEQWORD 
    }, 
    {   // 0x7c24
        MOVE_DSZ64_IMM(RDX, 0x6469),
        CONCAT_DSZ16_IMM(RDX, RDX, 0x7570),
        NOP,
        END_SEQWORD 
    }, 
};