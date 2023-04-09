unsigned long addr = 0x7de0;
ucode_t ucode_patch[] = {
    {   // 0x7de0
        ZEROEXT_DSZ32_DI(TMP0, 0x0),
        ZEROEXT_DSZ32_DI(TMP9, 0x303),
        SHL_DSZ32_DRI(TMP9, TMP9, 0x8),
        NOP_SEQWORD 
    }, 
    {   // 0x7de4
        MOVETOCREG_DSZ64_RI(TMP9, 0x6a1),
        MOVETOCREG_DSZ64_RI(TMP0, 0x6a0),
        // write match&patch [0, 0x20]
        WRMSLOOPCTRFBR_I(0x20),
        NOP_SEQWORD
    },
    {   // 0x7de8
        MOVETOCREG_DSZ64_RI(TMP0, 0x6a4),
        MOVETOCREG_DSZ64_RI(TMP0, 0x6a4),
        TESTUSTATE_UCODE(UST_MSLOOPCTR_NONZERO),
        SEQ_GOTO2( (addr + 8 ) )
    },
    {   // 0x7dec
        MOVETOCREG_DSZ64_RI(TMP0, 0x6a1),
        ZEROEXT_DSZ32_DI(RAX, 0x1337),
        CONCAT_DSZ16_DRI(RAX, RAX, 0x1337),
        END_SEQWORD
    }
};
