#include "udbg.h"

u_result_t udbgrd(uint64_t type, uint64_t addr) {
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

u_result_t udbgwr(uint64_t type, uint64_t addr, uint64_t value) {
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


uint64_t ucode_invoke(uint64_t addr) {
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

u64 ucode_invoke_2(u64 addr, u64 arg1, u64 arg2) {
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

u64 ucode_invoke_3(u64 addr, u64 arg1, u64 arg2, u64 arg3) {
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
