#ifndef PATCH_H_
#define PATCH_H_
#include "misc.h"

u64 ucode_addr_to_patch_addr(u64 addr);
u64 patch_addr_to_ucode_addr(u64 addr);
u64 ucode_addr_to_patch_seqword_addr(u64 addr);
void patch_ucode(u64 addr, ucode_t ucode_patch[], int n);
void init_match_and_patch(void);
void hook_match_and_patch(u64 entry_idx, u64 ucode_addr, u64 patch_addr);
u64 ldat_array_read(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr);
void do_fix_IN_patch();
void print_patch(u64 addr, ucode_t ucode_patch[], int n);

#endif // PATCH_H_
