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

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef struct {
    u64 value;
    u64 status;
} result;


#define mfence() asm volatile("mfence\n")
#define lfence() asm volatile("lfence\n")
#define lmfence() asm volatile("lfence\n mfence\n")
#define wbinvd() asm volatile("wbinvd\n")

__attribute__((always_inline))
result static inline udbgrd(uint64_t type, uint64_t addr) {
    lmfence();
    result res;
    asm volatile(
        ".byte 0x0F, 0x0E\n\t"
        : "=d" (res.value)
        , "=b" (res.status)
        : "a" (addr)
        , "c" (type)
    );
    lmfence();
    return res;
}

#define SIMPLERD(name, type) \
__attribute__((always_inline)) \
u64 static inline name(u64 addr) { \
    return (u64)udbgrd(type, addr).value; \
}

SIMPLERD(crbus_read, 0x00)
SIMPLERD(uram_read, 0x10)
SIMPLERD(io8_read, 0x18)
SIMPLERD(io16_read, 0x48)
SIMPLERD(io32_read, 0x50)
SIMPLERD(io64_read, 0x58)
SIMPLERD(staging_read, 0x80)
SIMPLERD(staging2_read, 0x40)

#undef SIMPLERD

#define STATUSRD(name, type) \
result static inline name(u64 addr) { \
 return udbgrd(type, addr); \
}

STATUSRD(sa_read, 0x08)

#undef STATUSRD

result static udbgwr(uint64_t type, uint64_t addr, uint64_t value) {
    uint32_t value_low = (uint32_t)(value & 0xFFFFFFFF);
    uint32_t value_high = (uint32_t)(value >> 32);
    result res;
    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "=d" (res.value)
        , "=b" (res.status)
        : "a" (addr)
        , "c" (type)
        , "d" (value_low)
        , "b" (value_high)
    );
    lmfence();
    return res;
}


__attribute__((always_inline))
uint64_t static inline ucode_invoke(uint64_t addr) {
    uint64_t rax = addr, rcx = 0xD8;
    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "+a" (rax)
        , "+c" (rcx)
        :
        : "rbx", "rdx", "rdi", "rsi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return rax;
}

__attribute__((always_inline))
u64 static inline ucode_invoke_2(u64 addr, u64 arg1, u64 arg2) {
    u64 rax = addr, rcx = 0xD8;

    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "+a" (rax)
        , "+c" (rcx)
        , "+rdi" (arg1)
        , "+rsi" (arg2)
        :
        : "rbx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return rax;
}

__attribute__((always_inline))
u64 static inline ucode_invoke_3(u64 addr, u64 arg1, u64 arg2, u64 arg3) {
    u64 rax = addr, rcx = 0xD8;

    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "+a" (rax)
        , "+c" (rcx)
        , "+rdi" (arg1)
        , "+rsi" (arg2)
        , "+rdx" (arg3)
        :
        : "rbx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return rax;
}

__attribute__((always_inline))
uint64_t static inline udbgwr_sideband(uint64_t port, uint64_t opcode, uint64_t value) {
    uint64_t rax = port, rcx = 0xc8, rbx = opcode, rdx = value;
    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "+a" (rax)
        , "+b" (rbx)
        , "+c" (rcx)
        , "+d" (rdx)
        :
        : "rdi", "rsi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return rax;
}

#define SIMPLEWR(name, type)     \
__attribute__((always_inline)) \
void static inline name(u64 addr, u64 value) { \
    udbgwr(type, addr, value); \
}

SIMPLEWR(crbus_write, 0x00)
SIMPLEWR(uram_write, 0x10)
SIMPLEWR(io8_write, 0x18)
SIMPLEWR(io16_write, 0x48)
SIMPLEWR(io32_write, 0x50)
SIMPLEWR(io64_write, 0x58)
SIMPLEWR(staging_write, 0x80)
SIMPLEWR(staging2_write, 0x40)

#undef SIMPLEWR

#define RBXWR(name, type) \
__attribute__((always_inline)) \
u64 static inline name(u64 addr, u64 value) { \
    return (u64)udbgwr(type, addr, value).status; \
}

RBXWR(sa_write, 0x08)

#undef RBXWR

#define RDXWR(name, type) \
__attribute__((always_inline)) \
u64 static inline name(u64 addr, u64 value) { \
    return (u64)udbgwr(type, addr, value).value; \
}

RDXWR(iosf_sb_write, 0xD0)

#undef RDXWR

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
