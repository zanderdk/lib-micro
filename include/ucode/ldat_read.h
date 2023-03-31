unsigned long addr = 0x7de0;
unsigned long ucode_patch[][4] = {
    {   // 0x7de0
        MOVE_DSZ64_REG(TMP0, RDI), 
        MOVE_DSZ64_REG(TMP1, RSI), 
        MOVE_DSZ64_REG(TMP2, RDX), 
        NOP_SEQWORD 
    }, 
    {   // 0x7de4
        ZEROEXT_DSZ32(TMP10, 0x0), 
        ADD_DSZ32_IMM(TMP11, TMP0, 0x1), 
        ADD_DSZ32_IMM(TMP12, TMP0, 0x2), 
        NOP_SEQWORD 
    }, 
    {   // 0x7de8
        // pause frontend
        MOVEFROMCREG_DSZ64_IMM(TMP9, 0x38c), 
        MOVETOCREG_DSZ64_IMM(TMP10, 0x38c), 
        MOVEFROMCREG_DSZ64_REG(TMP13, TMP11), 
        NOP_SEQWORD 
    }, 
    {   // 0x7dec
        MOVETOCREG_DSZ64_REG(TMP1, TMP11), 
        MOVETOCREG_DSZ64_REG(TMP2, TMP0), 
        MOVEFROMCREG_DSZ64_REG(RAX, TMP12), 
        NOP_SEQWORD 
    }, 
    {   // 0x7df0
        MOVETOCREG_DSZ64_REG(TMP10, TMP11), 
        MOVETOCREG_DSZ64_IMM(TMP9, 0x38c), 
        NOP, 
        END_SEQWORD 
    }, 
};
