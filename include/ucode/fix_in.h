unsigned long addr = 0x7c00;
unsigned long hook_address = 0x58ba;
unsigned long ucode_patch[][4] = {
    { UJMP(0x017a), NOP, NOP, END_SEQWORD }, // 0x7c00
};