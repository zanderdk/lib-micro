unsigned long addr = 0x7c10;
unsigned long ucode_patch[][4] = {
    {   // 0x7c10
        // 1) save all the registers to restore them
        // NOTICE: assume no one else uses [0xba00, 0xbb00] in the staging buffer
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(R10, 0xba40),
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(R11, 0xba80),
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(R12, 0xbac0),
        NOP_SEQWORD
    },
    {   // 0x7c14
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(R13, 0xbb00),
        // 2) remove the hook in the match&patch assuming it is at 0
        ZEROEXT_DSZ32_DI(R10, 0x0),
        // pause frontend
        MOVEFROMCREG_DSZ64_DI(R12, 0x38c),
        NOP_SEQWORD
    },
    {   // 0x7c18
        MOVETOCREG_DSZ64_RI(R10, 0x38c),
        // write match&patch at location 0 with the value of 0
        ZEROEXT_DSZ32_DI(R13, 0x303),
        SHL_DSZ32_DRI(R13, R13, 0x8),
        NOP_SEQWORD
    },
    {   // 0x7c20
        MOVETOCREG_DSZ64_RI(R13, 0x6a1),
        MOVETOCREG_DSZ64_RI(R10, 0x6a0),
        MOVETOCREG_DSZ64_RI(R10, 0x6a4),
        NOP_SEQWORD
    },
    {   // 0x7c24
        MOVETOCREG_DSZ64_RI(R10, 0x6a4),
        MOVETOCREG_DSZ64_RI(R10, 0x6a1),
        // restore frontend
        MOVETOCREG_DSZ64_RI(R12, 0x38c),
        NOP_SEQWORD
    },
    {   // 0x7c28
        // save RIP
        MOVEFROMCREG_DSZ64_DI(R10, CORE_CR_CUR_RIP),
        WRITEURAM_RI(R10, 0x69),
        // write clock value to tracing location
        MOVEFROMCREG_DSZ64_DI(R10, 0x2d7) | MOD1,
        NOP_SEQWORD
    },
    {   // 0x7c2c
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(R10, 0xba00),
        LDSTGBUF_DSZ64_ASZ16_SC1_DI(R10, 0xba40),
        LDSTGBUF_DSZ64_ASZ16_SC1_DI(R11, 0xba80),
        NOP_SEQWORD
    },
    {   // 0x7c30
        LDSTGBUF_DSZ64_ASZ16_SC1_DI(R12, 0xbac0),
        LDSTGBUF_DSZ64_ASZ16_SC1_DI(R13, 0xbb00),
        UJMP_I(tracing_addr),
        NOP_SEQWORD
    }
};
