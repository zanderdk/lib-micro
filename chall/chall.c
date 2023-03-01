#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdint.h>   // for uint32_t
#include <limits.h>   // for CHAR_BIT
#include <assert.h>
#include <unistd.h>

#define mfence() asm volatile("mfence\n")
#define lfence() asm volatile("lfence\n")
#define lmfence() asm volatile("lfence\n mfence\n")
#define wbinvd() asm volatile("wbinvd\n")

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


__attribute__((always_inline))
result static inline udbgwr(uint64_t type, uint64_t addr, uint64_t value) {
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
        : "rbx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "memory"
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
        : "rbx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "memory"
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

#define SIMPLEWR(name, val_t, addr_t, type)     \
__attribute__((always_inline)) \
void static inline name(addr_t addr, val_t value) { \
    udbgwr(type, addr, value); \
}

SIMPLEWR(uram_write, uint64_t, uint64_t, 0x10)

#undef SIMPLEWR

__attribute__((always_inline))
static inline uint32_t rotl32 (uint32_t n, unsigned int c)
{
  const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);  // assumes width is a power of 2.

  // assert ( (c<=mask) &&"rotate by type width or more");
  c &= mask;
  return (n<<c) | (n>>( (-c)&mask ));
}

__attribute__((always_inline))
static inline uint32_t rotr32 (uint32_t n, unsigned int c)
{
  const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);

  // assert ( (c<=mask) &&"rotate by type width or more");
  c &= mask;
  return (n>>c) | (n<<( (-c)&mask ));
}

#define K1 0xe4fbbdd9
#define K2 0xf6b983fd
#define K3 0x71021053
#define K4 0x27428645
#define K1_ROR rotr32(K1, 11)
#define K2_ROR rotr32(K2, 12)
#define K3_ROR rotr32(K3, 13)
#define K4_ROR rotr32(K4, 14)

#define DELTA_K 0xDC691A7F
#define DELTA_ROR rotr32(DELTA_K, 15)

#define SUM ((DELTA_K << 5) & 0xFFFFFFFF)
#define SUM_ROR rotr32(SUM, 16)


#define SECTION( S ) __attribute__ ((section ( S )))
void setup(void) {
    uram_write(0x28+0, K1_ROR);
    uram_write(0x28+1, K2_ROR);
    uram_write(0x28+2, K3_ROR);
    uram_write(0x28+3, K4_ROR);
    uram_write(0x28+4, DELTA_ROR);
    uram_write(0x28+5, SUM_ROR);
}

void (*init_it)(void) SECTION(".ctors") = setup;

char encrypted_flag[] = "\x94\xd9\x30\xdb\x25\xfc\x1c\x5e\x8d\x83\x0e\x14\xa9\x3a\x33\x5d\x17\x87\x2c\x63\x76\xa1\x3f\x6f\xae\x1c\x1f\x6d\x31\x8f\xe8\x11\x63\x6b\xc6\x69\xdf\xf3\x02\x9b\x22\x3a\xaf\x10\x30\x38\xab\x29\x5f\x95\x03\x96\xbb\x50\x6f\x75\xb9\x39\x3e\x74\x74\x12\x6a\xbe\x92\xb7\x36\x13\xb2\xec\x3d\xfd\xb9\x1b\x78\xef\xd7\x78\x5d\xa5";

__attribute__((always_inline))
uint64_t static inline RETURN() {
    asm volatile(
        "vmxoff\n\t"
    );
}

__attribute__((always_inline))
uint64_t static inline CALL_ARG1(u64 addr, u64 arg) {
    asm volatile(
        "vmxon [%0]\n\t"
        : "+r" (addr)
        : "D" (arg)
        : "rax", "memory"
    );
}

__attribute__((always_inline))
uint64_t static inline CALL_ARG2(u64 addr, u64 arg, u64 arg2) {
    asm volatile(
        "vmxon [%0]\n\t"
        : "+r" (addr)
        : "D" (arg)
        , "S" (arg2)
        : "rax", "memory"
    );
}

__attribute__((always_inline))
uint64_t static inline CALL_ARG3(u64 addr, u64 arg, u64 arg2, u64 arg3) {
    asm volatile(
        "vmxon [%0]\n\t"
        : "+r" (addr)
        : "D" (arg)
        , "S" (arg2)
        , "d" (arg3)
        : "rax", "memory"
    );
}

typedef struct {
    u32 k[4];
    u32 delta, sum;
} crypto_info;

__attribute__((always_inline))
void static inline get_crypto_info(volatile crypto_info *c) {
    asm volatile(
        /* "int3\n\tvmclear [rdi]\n\t" */
        "vmclear [rdi]\n\t"
        :
        : "D" (c)
        : "memory"
    );
}
void _decrypt (uint32_t *v);
void decrypt(void *p, int len);

crypto_info crypto;
__attribute__((noreturn))
void _decrypt (uint32_t *v) {
    get_crypto_info(&crypto);
    uint32_t v0=v[0], v1=v[1];

    uint32_t sum=crypto.sum, i;  /* set up; sum is (delta << 5) & 0xFFFFFFFF */
    uint32_t delta=crypto.delta;                     /* a key schedule constant */
    uint32_t k0=crypto.k[0], k1=crypto.k[1], k2=crypto.k[2], k3=crypto.k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
    asm volatile("pop rax\n\tpop rax\n\tpop rax");
    RETURN();
}

__attribute__((noreturn))
void _write(int fd, char *buf, uint64_t len) {
    asm volatile(
        "syscall\n\t"
        :
        : "a" (1)
        , "D" (fd)
        , "S" (buf)
        , "d" (len)
    );
    RETURN();
}

u64 _dec = (u64) &_decrypt;
__attribute__((noreturn))
void decrypt(void *p, int len) {
    for (int i = 0; i < len; i+=8) {
        CALL_ARG1( (u64) (&_dec), (u64) (p+i));
    }
    RETURN();
}


u64 dec = (u64) &decrypt;
u64 wr = (u64) &_write;
int main(void) {
    asm volatile("hlt");
    CALL_ARG2((u64) &dec, (u64) encrypted_flag, (u64) 0x50);
    CALL_ARG3((u64) &wr, 1, (u64) encrypted_flag, (u64) 0x50);
    return 0;
}
