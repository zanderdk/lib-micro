#include "patch.h"
#include "ldat.h"
#include "ucode_macro.h"

/* extern u8 verbose; */

u64 ucode_addr_to_patch_addr(u64 addr) {
    u64 base = addr - 0x7c00;
    // the last *4 does not make any sense but the CPU divides the address where
    // to write by for, still unkown reasons
    return ((base%4) * 0x80 + (base/4)) * 4;
}

u64 patch_addr_to_ucode_addr(u64 addr) {
    // NOTICE: the ucode_addr_to_patch_addr has a *4 more, so this will not be
    // the inverse
    u64 mul = addr % 0x80;
    u64 off = addr / 0x80;
    return 0x7c00 + mul*4 + off;
}

u64 ucode_addr_to_patch_seqword_addr(u64 addr) {
    u64 base = addr - 0x7c00;
    u64 seq_addr = ((base%4) * 0x80 + (base/4));
    return seq_addr % 0x80;
}

void patch_ucode(u64 addr, unsigned long ucode_patch[][4], int n) {
    // format: uop0, uop1, uop2, seqword
    // uop3 is fixed to a nop and cannot be overridden
    for (int i = 0; i < n; i++) {
        // patch ucode
        ms_rw_code_write(ucode_addr_to_patch_addr(addr + i*4)+0, CRC_UOP(ucode_patch[i][0]));
        ms_rw_code_write(ucode_addr_to_patch_addr(addr + i*4)+1, CRC_UOP(ucode_patch[i][1]));
        ms_rw_code_write(ucode_addr_to_patch_addr(addr + i*4)+2, CRC_UOP(ucode_patch[i][2]));
        // patch seqword
        ms_rw_seq_write(ucode_addr_to_patch_seqword_addr(addr) + i, CRC_SEQ(ucode_patch[i][3]));
    }
}

void init_match_and_patch(void) {
    #include "ucode/match_and_patch_init.h"
    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    u64 ret = ucode_invoke(addr);
    /* if (verbose) */
    /*     printf("init_match_and_patch: %lx\n", ret); */
    enable_match_and_patch();
}

void hook_match_and_patch(u64 entry_idx, u64 ucode_addr, u64 patch_addr) {
    if (ucode_addr % 2 != 0) {
        printf("[-] uop address must be even\n");
        return;
    }
    if (patch_addr % 2 != 0 || patch_addr < 0x7c00) {
        printf("[-] patch uop address must be even and >0x7c00\n");
        return;
    }

    u64 poff = (patch_addr - 0x7c00) / 2;
    u64 patch_value = 0x3e000000 | (poff << 16) | ucode_addr | 1;

    #include "ucode/match_and_patch_hook.h"
    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    u64 ret = ucode_invoke_2(addr, patch_value, entry_idx<<1);
    /* if (verbose) */
    /*     printf("hook_match_and_patch: %lx\n", ret); */
}

u64 ldat_array_read(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr) {
    #include "ucode/ldat_read.h"
    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    u64 array_bank_sel = 0x10000 | ((dword_idx & 0xf) << 12) | ((array_sel & 0xf) << 8) | (bank_sel & 0xf);
    u64 res = ucode_invoke_3(addr, pdat_reg, array_bank_sel, 0xc00000 | fast_addr);
    return res;
}

void do_fix_IN_patch() {
    #include "ucode/fix_in.h"
    /* if (verbose) */
    /*     printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr)); */
    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    hook_match_and_patch(0x1f, hook_address, addr);
}
