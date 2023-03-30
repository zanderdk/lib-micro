#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/io.h>
#include "udbg.h"

__attribute__((always_inline))
u64 static inline sa_write_opcode(u64 addr, u64 value, uint32_t opcode) {
    return (u64)udbgwr(0xC8, addr, (uint64_t)value | ((uint64_t)opcode << 32)).status;
}

__attribute__((always_inline))
static inline void patch_ucode(u64 addr, unsigned long ucode_patch[][4], int n);

__attribute__((always_inline))
static inline u64 ldat_array_read(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr);

__attribute__((always_inline))
static inline void ldat_array_write(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val) {
    u64 prev = crbus_read(0x692);
    crbus_write(0x692, prev | 1);

    crbus_write(pdat_reg + 1, 0x30000 | ((dword_idx & 0xf) << 12) | ((array_sel & 0xf) << 8) | (bank_sel & 0xf));
    crbus_write(pdat_reg, 0x000000 | (fast_addr & 0xffff));
    crbus_write(pdat_reg + 4, val & 0xffffffff);
    crbus_write(pdat_reg + 5, (val >> 32) & 0xffff);
    crbus_write(pdat_reg + 1, 0);

    crbus_write(0x692, prev);
}


__attribute__((always_inline))
static inline void ms_array_write(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val) {
    ldat_array_write(0x6a0, array_sel, bank_sel, dword_idx, fast_addr, val);
}

static inline u64 ms_array_read(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr) {
    return ldat_array_read(0x6a0, array_sel, bank_sel, dword_idx, fast_addr);
}

//read only:
//array0 = ro code
//array1 = ro sequence

//writeable:
//array2 = wr sequence
//array3 = match and patch
//array4 = rw code

//read funcs:
//
__attribute__((always_inline))
static inline u64 ms_patch_ram_read(u64 addr) {
    return ms_array_read(4, 0, 0, addr);
}
 
__attribute__((always_inline))
static inline u64 ms_match_patch_read(u64 addr) {
    return ms_array_read(3, 0, 0, addr);
}

__attribute__((always_inline))
static inline u64 ms_const_read(u64 addr) {
    return ms_array_read(2, 0, 0, addr);
}

__attribute__((always_inline))
static inline u64 ms_array1_read(u64 addr) {
    return ms_array_read(1, 0, 0, addr);
}

__attribute__((always_inline))
static inline u64 ms_array0_read(u64 addr) {
    return ms_array_read(0, 0, 0, addr);
}

//write funcs:
__attribute__((always_inline))
static inline void ms_patch_ram_write(u64 addr, u64 val) {
    ms_array_write(4, 0, 0, addr, val);
}

__attribute__((always_inline))
static inline void ms_match_patch_write(u64 addr, u64 val) {
    ms_array_write(3, 0, 0, addr, val);
}

__attribute__((always_inline))
static inline void ms_const_write(u64 addr, u64 val) {
    ms_array_write(2, 0, 0, addr, val);
}

__attribute__((always_inline))
static inline u64 ucode_addr_to_patch_addr(u64 addr) {
    u64 base = addr - 0x7c00;
    // the last *4 does not make any sense but the CPU divides the address where
    // to write by for, still unkown reasons
    return ((base%4) * 0x80 + (base/4)) * 4;
}

__attribute__((always_inline))
static inline u64 patch_addr_to_ucode_addr(u64 addr) {
    // NOTICE: the ucode_addr_to_patch_addr has a *4 more, so this will not be
    // the inverse
    u64 mul = addr % 0x80;
    u64 off = addr / 0x80;
    return 0x7c00 + mul*4 + off;
}

__attribute__((always_inline))
static inline u64 ucode_addr_to_patch_seqword_addr(u64 addr) {
    u64 base = addr - 0x7c00;
    u64 seq_addr = ((base%4) * 0x80 + (base/4));
    return seq_addr % 0x80;
}

void enable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp & ~1uL);
}

void disable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp | 1uL);
}

void ms_array_dump(u64 array_sel, u64 fast_addr, u64 size) {

    for (; fast_addr < size; fast_addr+=4) {
    	//usleep(0x20000);
        u64 val0 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr);
        //usleep(0x20000);
        u64 val1 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+1);
        //usleep(0x20000);
        u64 val2 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+2);
        //usleep(0x20000);
        u64 val3 = ldat_array_read(0x6a0, array_sel, 0, 0, fast_addr+3);
        printf("%04lx: %012lx %012lx %012lx %012lx\n", fast_addr, val0, val1, val2, val3);
    }
}

void ms_rom_dump(void){
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




#endif // MAIN_H_
