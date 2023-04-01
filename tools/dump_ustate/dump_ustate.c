#define _GNU_SOURCE

#include <argp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "misc.h"
#include "ldat.h"
#include "patch.h"

#include "ucode_macro.h"

void persistent_trace(u64 addr, u64 hook_address, u64 idx) {
    u64 uop0 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+0) & CRC_UOP_MASK;
    u64 uop1 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+1) & CRC_UOP_MASK;
    u64 uop2 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+2) & CRC_UOP_MASK;
    u64 seqw = ldat_array_read(0x6a0, 1, 0, 0, hook_address)   & CRC_SEQ_MASK;

    printf("uop0: 0x%012lx\n", uop0);
    printf("uop1: 0x%012lx\n", uop1);
    printf("uop2: 0x%012lx\n", uop2);
    printf("seqw: 0x%08lx\n", seqw);

    unsigned long ucode_patch[][4] = {
        {
            MOVE_DSZ64_IMM(RBX, 0x1337), NOP, NOP, END_SEQWORD
        },
    };

    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    hook_match_and_patch(idx, hook_address, addr);
}

general_purpose_regs try_xlat(u64 val) {
    u64 rax = val;
    general_purpose_regs result;
    lmfence();
    asm volatile(
        "vmxon [rbx]\n\t"
        : "+a" (result.rax)
        , "=b" (result.rbx)
        , "=c" (result.rcx)
        , "=d" (result.rdx)
        :
        : "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return result;
}

void test_ucode(void) {
    u64 vmxon_xlat = 0x0ae8;
    u64 uaddr = 0x7c20;
    persistent_trace(uaddr, vmxon_xlat, 0);
    general_purpose_regs val = try_xlat(0xdeaddeaddeaddeadUL);
    printf("rax:        0x%lx\n", val.rax);
    printf("rbx:        0x%lx\n", val.rbx);
    printf("rcx:        0x%lx\n", val.rcx);
    printf("rdx:        0x%lx\n", val.rdx);
    puts("");
}


int main(int argc, char* argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    assign_to_core(3);

    init_match_and_patch();
    do_fix_IN_patch();

    test_ucode();

    return 0;
}
