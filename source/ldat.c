#include "ldat.h"
#include "udbg.h"

void ldat_array_write(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val) {
    u64 prev = crbus_read(0x692);
    crbus_write(0x692, prev | 1);

    crbus_write(pdat_reg + 1, 0x30000 | ((dword_idx & 0xf) << 12) | ((array_sel & 0xf) << 8) | (bank_sel & 0xf));
    crbus_write(pdat_reg, 0x000000 | (fast_addr & 0xffff));
    crbus_write(pdat_reg + 4, val & 0xffffffff);
    crbus_write(pdat_reg + 5, (val >> 32) & 0xffff);
    crbus_write(pdat_reg + 1, 0);

    crbus_write(0x692, prev);
}

void ms_array_write(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val) {
    ldat_array_write(0x6a0, array_sel, bank_sel, dword_idx, fast_addr, val);
}

u64 ms_array_read(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr) {
    return ldat_array_read(0x6a0, array_sel, bank_sel, dword_idx, fast_addr);
}
