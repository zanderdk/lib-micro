unsigned long addr = ualloc(13);
unsigned long hook_address = 0x0be0;
unsigned long ucode_patch[][4] = {
    {   // 0x0
        MOVE_DSZ64_IMM(TMP2, 0x8000), 
        CONCAT_DSZ16_IMM(TMP2, TMP2, 0x2), 
        XOR_DSZ64_REG(TMP0, TMP2, RAX),
        NOP_SEQWORD,
    },
    {   // 0x4
        UJMPCC_DIRECT_NOTTAKEN_CONDZ(TMP0, addr + 0x10), 
        ADD_DSZ32_IMM(TMP2, TMP2, 0x1),
        XOR_DSZ64_REG(TMP0, TMP2, RAX),
        NOP_SEQWORD
    },
    {   // 0x8
        UJMPCC_DIRECT_NOTTAKEN_CONDZ(TMP0, addr + 0x1c), 
        ADD_DSZ32_IMM(TMP2, TMP2, 0x1),
        XOR_DSZ64_REG(TMP0, TMP2, RAX),
        NOP_SEQWORD
    },
    {   // 0xc
        UJMPCC_DIRECT_NOTTAKEN_CONDZ(TMP0, addr + 0x28), 
        MOVE_DSZ64_IMM(TMP0, 0xa), 
        NOP,
        SEQ_GOTO2(0x4808) 
    },

    {   // 0x10
        MOVE_DSZ64_IMM(RAX, 0x7473),
        CONCAT_DSZ16_IMM(RAX, RAX, 0x7563),
        MOVE_DSZ64_IMM(RBX, 0x632d),
        NOP_SEQWORD
    },
    {   // 0x14
        CONCAT_DSZ16_IMM(RBX, RBX, 0x6d6f),
        MOVE_DSZ64_IMM(RCX, 0x6620),
        CONCAT_DSZ16_IMM(RCX, RCX, 0x7570),
        NOP_SEQWORD
    },
    {   // 0x18
        MOVE_DSZ64_IMM(RDX, 0x4720),
        CONCAT_DSZ16_IMM(RDX, RDX, 0x726f),
        NOP,
        END_SEQWORD
    },

    {   // 0x1c
        MOVE_DSZ64_IMM(RAX, 0x6d64),
        CONCAT_DSZ16_IMM(RAX, RAX, 0x6c6f),
        MOVE_DSZ64_IMM(RBX, 0x2074),
        NOP_SEQWORD
    },
    {   // 0x20
        CONCAT_DSZ16_IMM(RBX, RBX, 0x6e6f),
        MOVE_DSZ64_IMM(RCX, 0x7a20),
        CONCAT_DSZ16_IMM(RCX, RCX, 0x7962),
        NOP_SEQWORD
    },
    {   // 0x24
        MOVE_DSZ64_IMM(RDX, 0x6564),
        CONCAT_DSZ16_IMM(RDX, RDX, 0x6e61),
        NOP,
        END_SEQWORD
    },

    {   // 0x28
        MOVE_DSZ64_IMM(RAX, 0x206b),
        CONCAT_DSZ16_IMM(RAX, RAX, 0x6472),
        MOVE_DSZ64_IMM(RBX, 0x2064),
        NOP_SEQWORD
    },
    {   // 0x2c
        CONCAT_DSZ16_IMM(RBX, RBX, 0x6e61),
        MOVE_DSZ64_IMM(RCX, 0x646c),
        CONCAT_DSZ16_IMM(RCX, RCX, 0x794d),
        NOP_SEQWORD
    },
    {   // 0x30
        MOVE_DSZ64_IMM(RDX, 0x006f),
        CONCAT_DSZ16_IMM(RDX, RDX, 0x7265),
        NOP,
        END_SEQWORD
    }
};