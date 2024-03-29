#ifndef UDBG_H_
#define UDBG_H_
#include "misc.h"
#include <string.h>

typedef struct {
    u64 value;
    u64 status;
} u_result_t;

__attribute__((always_inline))
u_result_t static inline udbgrd(uint64_t type, uint64_t addr) {
    lmfence();
    u_result_t res;
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

__attribute__((always_inline))
u_result_t static inline udbgwr(uint64_t type, uint64_t addr, uint64_t value) {
    uint32_t value_low = (uint32_t)(value & 0xFFFFFFFF);
    uint32_t value_high = (uint32_t)(value >> 32);
    u_result_t res;
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
general_purpose_regs static inline generic_ucode_invoke(uint64_t addr) {
    general_purpose_regs regs;
    memset(&regs, 0, sizeof(regs));
    regs.rcx = 0xD8;
    regs.rax = addr;
    lmfence();
    asm volatile(
        ".byte 0x0F, 0x0F\n\t"
        : "+a" (regs.rax)
        , "+b" (regs.rbx)
        , "+c" (regs.rcx)
        , "+d" (regs.rdx)
        :
        : "rdi", "rsi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return regs;
}

__attribute__((always_inline))
u64 static inline ucode_invoke_2(u64 addr, u64 arg1, u64 arg2) {
    uint64_t rax = addr, rcx = 0xD8;
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
__attribute__((always_inline)) \
u_result_t static inline name(u64 addr) { \
 return udbgrd(type, addr); \
}

STATUSRD(sa_read, 0x08)

#undef STATUSRD

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

uint64_t ucode_invoke(uint64_t addr);
u64 ucode_invoke_2(u64 addr, u64 arg1, u64 arg2);
u64 ucode_invoke_3(u64 addr, u64 arg1, u64 arg2, u64 arg3);
#endif // UDBG_H_
