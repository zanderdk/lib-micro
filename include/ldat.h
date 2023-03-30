#ifndef LDAT_H_
#define LDAT_H_
#include "misc.h"
#include "udbg.h"

void ldat_array_write(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val);
void ms_array_write(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val);
u64 ms_array_read(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr);

//read only:
//array0 = ro code
//array1 = ro sequence word

//writeable:
//array2 = wr sequence word
//array3 = match and patch
//array4 = rw code
u64 static ms_array_0_read(u64 addr) {return ms_array_read(0, 0, 0, addr); }
u64 static ms_array_1_read(u64 addr) {return ms_array_read(1, 0, 0, addr); }
u64 static ms_array_2_read(u64 addr) {return ms_array_read(2, 0, 0, addr); }
u64 static ms_array_3_read(u64 addr) {return ms_array_read(3, 0, 0, addr); }
u64 static ms_array_4_read(u64 addr) {return ms_array_read(4, 0, 0, addr); }

__attribute__((weak, alias("ms_array_0_read")))
u64 ms_ro_code_read(u64 addr);

__attribute__((weak, alias("ms_array_1_read")))
u64 ms_ro_seq_read(u64 addr);

__attribute__((weak, alias("ms_array_2_read")))
u64 ms_rw_seq_read(u64 addr);

__attribute__((weak, alias("ms_array_3_read")))
u64 ms_match_n_patch_read(u64 addr);

__attribute__((weak, alias("ms_array_4_read")))
u64 ms_rw_code_read(u64 addr);


void static ms_array_2_write(u64 addr, u64 val) {return ms_array_write(2, 0, 0, addr, val); }
void static ms_array_3_write(u64 addr, u64 val) {return ms_array_write(3, 0, 0, addr, val); }
void static ms_array_4_write(u64 addr, u64 val) {return ms_array_write(4, 0, 0, addr, val); }

__attribute__((weak, alias("ms_array_2_write")))
void ms_rw_seq_write(u64 addr, u64 val);

__attribute__((weak, alias("ms_array_3_write")))
void ms_match_n_patch_write(u64 addr, u64 val);

__attribute__((weak, alias("ms_array_4_write")))
void ms_rw_code_write(u64 addr, u64 val);

void static enable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp & ~1uL);
}

void static disable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp | 1uL);
}

#endif // LDAT_H_
