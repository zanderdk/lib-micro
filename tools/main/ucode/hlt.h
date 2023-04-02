unsigned long addr = 0x7d00;
unsigned long hook_address = 0x07c8;
unsigned long ucode_patch[][4] = {
    {   //0x7d00
        READURAM_DI(TMP0, 0x28), 
        ADD_DSZ64_DRI(TMP0, TMP0, 0x1), 
        WRITEURAM_RI(TMP0, 0x28), 
        END_SEQWORD 
    },
};