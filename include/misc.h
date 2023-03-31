#ifndef MISC_H_
#define MISC_H_
#define _GNU_SOURCE

#include <stdint.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

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
    u64 rax;
    u64 rbx;
    u64 rcx;
    u64 rdx;
} genral_purpose_regs;

#define ARRAY_SZ(arr) \
    sizeof(arr)/sizeof(arr[0])

#define mfence() asm volatile("mfence\n")
#define lfence() asm volatile("lfence\n")
#define lmfence() asm volatile("lfence\n mfence\n")
#define wbinvd() asm volatile("wbinvd\n")

void assign_to_core(int core_id);
#endif // MISC_H_
