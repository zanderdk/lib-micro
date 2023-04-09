unsigned long addr = 0x7c10;
unsigned long hook_address = 0x0be0;
ucode_t ucode_patch[] = {
    {   // 0x7c10
        MOVE_DSZ64_DI(TMP2, 0x8000), 
        CONCAT_DSZ16_DRI(TMP2, TMP2, 0x2), 
        XOR_DSZ64_DRR(TMP0, TMP2, RAX),
        NOP_SEQWORD,
    },
    {   // 0x7c14
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(TMP0, 0x7c20), 
        ADD_DSZ32_DRI(TMP2, TMP2, 0x1),
        XOR_DSZ64_DRR(TMP0, TMP2, RAX),
        NOP_SEQWORD
    },
    {   // 0x7c18
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(TMP0, 0x7c2c), 
        ADD_DSZ32_DRI(TMP2, TMP2, 0x1),
        XOR_DSZ64_DRR(TMP0, TMP2, RAX),
        NOP_SEQWORD
    },
    {   // 0x7c18
        UJMPCC_DIRECT_NOTTAKEN_CONDZ_RI(TMP0, 0x7c38), 
        MOVE_DSZ64_DI(TMP0, 0xa), 
        NOP,
        SEQ_GOTO2(0x4808) 
    },

    {   // 0x7c20
        MOVE_DSZ64_DI(RAX, 0x7473),
        CONCAT_DSZ16_DRI(RAX, RAX, 0x7563),
        MOVE_DSZ64_DI(RBX, 0x632d),
        NOP_SEQWORD
    },
    {   // 0x7c24
        CONCAT_DSZ16_DRI(RBX, RBX, 0x6d6f),
        MOVE_DSZ64_DI(RCX, 0x6620),
        CONCAT_DSZ16_DRI(RCX, RCX, 0x7570),
        NOP_SEQWORD
    },
    {   // 0x7c28
        MOVE_DSZ64_DI(RDX, 0x4720),
        CONCAT_DSZ16_DRI(RDX, RDX, 0x726f),
        NOP,
        END_SEQWORD
    },

    {   // 0x7c2c
        MOVE_DSZ64_DI(RAX, 0x6d64),
        MOVE_DSZ64_DRI(RAX, RAX, 0x6c6f),
        MOVE_DSZ64_DI(RBX, 0x2074),
        NOP_SEQWORD
    },
    {   // 0x7c30
        MOVE_DSZ64_DRI(RBX, RBX, 0x6e6f),
        MOVE_DSZ64_DI(RCX, 0x7a20),
        MOVE_DSZ64_DRI(RCX, RCX, 0x7962),
        NOP_SEQWORD
    },
    {   // 0x7c34
        MOVE_DSZ64_DI(RDX, 0x6564),
        MOVE_DSZ64_DRI(RDX, RDX, 0x6e61),
        NOP,
        END_SEQWORD
    },

    {   // 0x7c38
        MOVE_DSZ64_DI(RAX, 0x206b),
        MOVE_DSZ64_DRI(RAX, RAX, 0x6472),
        MOVE_DSZ64_DI(RBX, 0x2064),
        NOP_SEQWORD
    },
    {   // 0x7c3c
        MOVE_DSZ64_DRI(RBX, RBX, 0x6e61),
        MOVE_DSZ64_DI(RCX, 0x646c),
        MOVE_DSZ64_DRI(RCX, RCX, 0x794d),
        NOP_SEQWORD
    },
    {   // 0x7c40
        MOVE_DSZ64_DI(RDX, 0x006f),
        MOVE_DSZ64_DRI(RDX, RDX, 0x7265),
        NOP,
        END_SEQWORD
    }
};