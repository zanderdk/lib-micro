#ifndef UDBG_H_
#define UDBG_H_

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

typedef uint128_t u128;
typedef int128_t s128;

typedef struct {
    u64 value;
    u64 status;
} u_result_t;


#define mfence() asm volatile("mfence\n")
#define lfence() asm volatile("lfence\n")
#define lmfence() asm volatile("lfence\n mfence\n")
#define wbinvd() asm volatile("wbinvd\n")

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
u_result_t static inline name(u64 addr) { \
 return udbgrd(type, addr); \
}

STATUSRD(sa_read, 0x08)

#undef STATUSRD

u_result_t static udbgwr(uint64_t type, uint64_t addr, uint64_t value) {
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


#endif // UDBG_H_
