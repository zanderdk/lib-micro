unsigned long addr = 0x7de0;
unsigned long ucode_patch[][4] = {
    {   // 0x7de0
        MOVE_DSZ64_REG(TMP0, RDI), 
        MOVE_DSZ64_REG(TMP1, RSI), 
        ZEROEXT_DSZ32(TMP10, 0x0), 
        NOP_SEQWORD 
    }, 
    {   // 0x7de4
        // pause frontend
        MOVEFROMCREG_DSZ64_IMM(TMP12, 0x38c), 
        MOVETOCREG_DSZ64_IMM(TMP10, 0x38c),
        // write match&patch at location tmp1 with the value of tmp0
        ZEROEXT_DSZ32(TMP9, 0x303),
        NOP_SEQWORD
    },
    {   // 0x7de8
        SHL_DSZ32_IMM(TMP9, TMP9, 0x8),
        MOVETOCREG_DSZ64_IMM(TMP9, 0x6a1),
        MOVETOCREG_DSZ64_IMM(TMP1, 0x6a0),
        NOP_SEQWORD
    },
    {   // 0x7dec
        MOVETOCREG_DSZ64_IMM(TMP0, 0x6a4),
        MOVETOCREG_DSZ64_IMM(TMP10, 0x6a4),
        MOVETOCREG_DSZ64_IMM(TMP10, 0x6a1),
        NOP_SEQWORD
    },
    {   // 0x7df0
        // restore frontend
        MOVETOCREG_DSZ64_IMM(TMP12, 0x38c),
        ZEROEXT_DSZ32(RAX, 0x1337),
        CONCAT_DSZ16_IMM(RAX, RAX, 0x1337),
        END_SEQWORD
    },
};
