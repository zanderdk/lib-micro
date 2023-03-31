#include "dump.h"
#include "udbg.h"
#include "patch.h"

void ms_array_dump(u64 array_sel, u64 fast_addr, u64 size) {

    for (; fast_addr < size; fast_addr+=4) {
        u64 val0 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr);
        u64 val1 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+1);
        u64 val2 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+2);
        u64 val3 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+3);
        printf("%04lx: %012lx %012lx %012lx %012lx\n", fast_addr, val0, val1, val2, val3);
    }
}

void ms_ro_dump(void){
    puts("array 00:");
    ms_array_dump(0, 0, 0x8000);
}

void ms_irom_dump(void){
    puts("array 01:");
    ms_array_dump(1, 0, 0x8000);
}

void ms_patch_consts_dump(void){
    puts("array 02:");
    ms_array_dump(2, 0, 0x80);
}

void ms_match_patch_regs_dump(void){
    puts("array 03:");
    ms_array_dump(3, 0, 0x20);
}

void ms_patch_ram_dump(void){
    puts("array 04:");
    ms_array_dump(4, 0, 0x200);
}

void uram_dump(void) {
    for (u64 i = 0; i < 0x100; i += 4) {
        u64 val0 = uram_read(i);
        u64 val1 = uram_read(i+1);
        u64 val2 = uram_read(i+2);
        u64 val3 = uram_read(i+3);
        printf("%04lx: %016lx %016lx %016lx %016lx\n", i, val0, val1, val2, val3);
    }
}
