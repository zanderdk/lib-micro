#ifndef DUMP_H_
#define DUMP_H_
#include "misc.h"

void ms_array_dump(u64 array_sel, u64 fast_addr, u64 size);
void ms_rom_dump(void);
void ms_irom_dump(void);
void ms_patch_consts_dump(void);
void ms_match_patch_regs_dump(void);
void ms_patch_ram_dump(void);
void uram_dump(void);

#endif // DUMP_H_
