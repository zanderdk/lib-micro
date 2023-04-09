ucode_t ucode_patch[] = {
    {   // 0x0
        MOVEFROMCREG_DSZ64_DI(testreg, CORE_CR_CUR_UIP),
        UJMP_I(addr+0xd),
        STADSTGBUF_DSZ64_ASZ16_SC1_RI(testreg, 0xba40),
        SEQ_GOTO0(addr+0x2) | SEQ_NOSYNC
    },
    {   // 0x4
        ZEROEXT_DSZ32_DI(testreg, 0xdead),
        CONCAT_DSZ16_DRR(testreg, testreg, testreg),
        CONCAT_DSZ32_DRR(testreg, testreg, testreg),
        NOP_SEQWORD
    },
    {   // 0x8
        XOR_DSZ64_DRR(testreg, testreg, RAX),
        UJMPCC_DIRECT_NOTTAKEN_CONDNZ_RI(testreg, addr+0xc),
        LDSTGBUF_DSZ64_ASZ16_SC1_DI(RAX, 0xba40),
        END_SEQWORD
    },
    {   // 0xc
        uop0, uop1, uop2, seqw
    },
    {   // 0x10
        UJMP_I(aligned_hook_address+4), UJMP_I(aligned_hook_address+5), UJMP_I(aligned_hook_address+6), SEQ_UEND0(2) | SEQ_NEXT | SEQ_NOSYNC
    }
};