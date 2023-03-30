#ifndef MAIN_H_
#define MAIN_H_
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/io.h>
#include "udbg.h"
#include "ldat.h"

void patch_ucode(u64 addr, unsigned long ucode_patch[][4], int n);
u64 ldat_array_read(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr);

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

#endif // MAIN_H_
