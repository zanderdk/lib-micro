unsigned long addr = 0x7de0;
ucode_t ucode_patch[] = {
    {   // 0x7de0
        MOVE_DSZ64_DR(TMP0, RDI), 
        MOVE_DSZ64_DR(TMP1, RSI), 
        MOVE_DSZ64_DR(TMP2, RDX), 
        NOP_SEQWORD 
    }, 
    {   // 0x7de4
        ZEROEXT_DSZ32_DI(TMP10, 0x0), 
        ADD_DSZ32_DRI(TMP11, TMP0, 0x1), 
        ADD_DSZ32_DRI(TMP12, TMP0, 0x2), 
        NOP_SEQWORD 
    }, 
    {   // 0x7de8
        // pause frontend
        MOVEFROMCREG_DSZ64_DI(TMP9, 0x38c), 
        MOVETOCREG_DSZ64_RI(TMP10, 0x38c), 
        MOVEFROMCREG_DSZ64_DR(TMP13, TMP11), 
        NOP_SEQWORD 
    }, 
    {   // 0x7dec
        MOVETOCREG_DSZ64_RR(TMP1, TMP11), 
        MOVETOCREG_DSZ64_RR(TMP2, TMP0), 
        MOVEFROMCREG_DSZ64_DR(RAX, TMP12), 
        NOP_SEQWORD 
    }, 
    {   // 0x7df0
        MOVETOCREG_DSZ64_RR(TMP10, TMP11), 
        MOVETOCREG_DSZ64_RI(TMP9, 0x38c), 
        NOP, 
        END_SEQWORD 
    }, 
};
