unsigned long addr = ualloc(8);
unsigned long ucode_patch[8][4] = {
    {   // 0x0
        // 1) save all the registers to restore them
        // NOTICE: assume no one else uses [0xba00, 0xbb00] in the staging buffer
        STADSTGBUF_DSZ64_ASZ16_SC1_IMM(R10, 0xba40),
        STADSTGBUF_DSZ64_ASZ16_SC1_IMM(R11, 0xba80),
        STADSTGBUF_DSZ64_ASZ16_SC1_IMM(R12, 0xbac0),
        NOP_SEQWORD
    },
    {   // 0x4
        STADSTGBUF_DSZ64_ASZ16_SC1_IMM(R13, 0xbb00),
        // 2) remove the hook in the match&patch assuming it is at 0
        ZEROEXT_DSZ32(R10, 0x0),
        // pause frontend
        MOVEFROMCREG_DSZ64_IMM(R12, 0x38c),
        NOP_SEQWORD
    },
    {   // 0x8
        MOVETOCREG_DSZ64_IMM(R10, 0x38c),
        // write match&patch at location 0 with the value of 0
        ZEROEXT_DSZ32(R13, 0x303),
        SHL_DSZ32_IMM(R13, R13, 0x8),
        NOP_SEQWORD
    },
    {   // 0xc
        MOVETOCREG_DSZ64_IMM(R13, 0x6a1),
        MOVETOCREG_DSZ64_IMM(R10, 0x6a0),
        MOVETOCREG_DSZ64_IMM(R10, 0x6a4),
        NOP_SEQWORD
    },
    {   // 0x10
        MOVETOCREG_DSZ64_IMM(R10, 0x6a4),
        MOVETOCREG_DSZ64_IMM(R10, 0x6a1),
        // restore frontend
        MOVETOCREG_DSZ64_IMM(R12, 0x38c),
        NOP_SEQWORD
    },
    {   // 0x14
        // save RIP
        MOVEFROMCREG_DSZ64_IMM(R10, CORE_CR_CUR_RIP),
        WRITEURAM_IMM(R10, 0x69),
        // write clock value to tracing location
        MOVEFROMCREG_DSZ64_IMM(R10, 0x2d7) | MOD1,
        NOP_SEQWORD
    },
    {   // 0x18
        STADSTGBUF_DSZ64_ASZ16_SC1_IMM(R10, 0xba00),
        LDSTGBUF_DSZ64_ASZ16_SC1_IMM(R10, 0xba40),
        LDSTGBUF_DSZ64_ASZ16_SC1_IMM(R11, 0xba80),
        NOP_SEQWORD
    },
    {   // 0x1c
        LDSTGBUF_DSZ64_ASZ16_SC1_IMM(R12, 0xbac0),
        LDSTGBUF_DSZ64_ASZ16_SC1_IMM(R13, 0xbb00),
        UJMP(tracing_addr),
        NOP_SEQWORD
    }
};
