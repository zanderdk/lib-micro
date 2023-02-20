#define _GNU_SOURCE

#include "main.h"


cpu_set_t set;
void assign_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset) != 0){
        puts("assign_to_core");
        exit(-1);
    }
}

__attribute__((always_inline))
static inline void patch_ucode(u64 addr, unsigned long ucode_patch[][4], int n) {
    // format: uop0, uop1, uop2, seqword
    // uop3 is fixed to a nop and cannot be overridden
    for (int i = 0; i < n; i++) {
        // patch ucode
        ms_patch_ram_write(ucode_addr_to_patch_addr(addr + i*4),   ucode_patch[i][0]);
        ms_patch_ram_write(ucode_addr_to_patch_addr(addr + i*4)+1, ucode_patch[i][1]);
        ms_patch_ram_write(ucode_addr_to_patch_addr(addr + i*4)+2, ucode_patch[i][2]);
        // patch seqword
        ms_const_write(ucode_addr_to_patch_seqword_addr(addr) + i, ucode_patch[i][3]);
    }
}

void init_match_and_patch(void) {
    #include "ucode/match_and_patch_init.h"
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    u64 ret = ucode_invoke(addr);
    printf("init_match_and_patch: %lx\n", ret);
    enable_match_and_patch();
}

static inline void hook_match_and_patch(u64 entry_idx, u64 ucode_addr, u64 patch_addr) {
    if (ucode_addr % 2 != 0) {
        printf("[-] uop address must be even\n");
        return;
    }
    if (patch_addr % 2 != 0 || patch_addr < 0x7c00) {
        printf("[-] patch uop address must be even and >0x7c00\n");
        return;
    }

    //TODO: try to hook odd addresses!!
    u64 poff = (patch_addr - 0x7c00) / 2;
    u64 patch_value = 0x3e000000 | (poff << 16) | ucode_addr | 1;
    
    #include "ucode/match_and_patch_hook.h"
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    u64 ret = ucode_invoke_2(addr, patch_value, entry_idx<<1);
    printf("hook_match_and_patch: %lx\n", ret);
}

__attribute__((always_inline))
static inline u64 ldat_array_read(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr) {
    #include "ucode/ldat_read.h"
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    u64 array_bank_sel = 0x10000 | ((dword_idx & 0xf) << 12) | ((array_sel & 0xf) << 8) | (bank_sel & 0xf);
    u64 res = ucode_invoke_3(addr, pdat_reg, array_bank_sel, 0xc00000 | fast_addr);
    return res;
}

void do_fix_IN_patch() {
    #include "ucode/fix_in.h"
    printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    hook_match_and_patch(0x1f, hook_address, addr);
}

void do_cpuid_patch() {
    #include "ucode/cpuid.h"
    printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    hook_match_and_patch(0, hook_address, addr);
}

#define END_UNKOWN_UOP (0x125600000000uL)
#define NOP_SEQWORD (0x0000300000c0uL)
#define END_SEQWORD (0x130000f2)
u64 make_seqw_goto_syncfull(u64 target_addr) {
    u64 seqw =  0x9000080 | ((target_addr & 0x7fff) << 8);
    return seqw | (parity0(seqw) << 28) | (parity1(seqw) << 29);
}
void insert_trace(u64 tracing_addr) {
	#include "ucode/trace.h"
	
    u64 n_tetrads = sizeof(ucode_patch) / sizeof(ucode_patch[0]);
    u64 seqw_goto = make_seqw_goto_syncfull(tracing_addr);
    u64 curr_seqw = ucode_patch[n_tetrads-1][3];
    if (curr_seqw != END_SEQWORD) {
        printf("[-] The tracing patch has no simple END_SEQWORD at the end\n");
        exit(-1);
    }
    ucode_patch[n_tetrads-1][3] = seqw_goto;
    if (ucode_patch[n_tetrads-1][0] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][0] = 0;
    if (ucode_patch[n_tetrads-1][1] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][1] = 0;
    if (ucode_patch[n_tetrads-1][2] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][2] = 0;
    
    patch_ucode(addr, ucode_patch, n_tetrads);
    hook_match_and_patch(0, tracing_addr, addr);   
}


typedef struct {
	u32 rax;
	u32 rbx;
	u32 rcx;
	u32 rdx;
} cpuinfo_res;

__attribute__((always_inline))
cpuinfo_res static inline cpuinfo(u64 arg1) {
    u64 rax = arg1;
    cpuinfo_res result;
    lmfence();
    asm volatile(
        "cpuid\n\t"
        : "=a" (result.rax)
        , "=b" (result.rbx)
        , "=c" (result.rcx)
        , "=d" (result.rdx)
        : "a" (rax)
        : "rdi", "rsi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
    lmfence();
    return result;
}


int main(int argc, char* argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    

    if (argc < 3) {
        printf("Usage: %s <r|t|c|d> <core> [...]\n", argv[0]);
        exit(-1);
    }
    
    int core = atoi(argv[2]);
    if (0 <= core && core <= 3) 
        assign_to_core(atoi(argv[2]));
    
    if (argv[1][0] == 'r') { // Reset match and patch
        init_match_and_patch();
        do_fix_IN_patch();
    }

    if (argv[1][0] == 't') { // Do trace
        if (argc < 4) {
            printf("Missing trace address arg\n");
            exit(-1);
        }

        uram_write(0x69, 0xd00df00d);
        u64 trace_addr;
        if (sscanf(argv[3], "%lx", &trace_addr) != 1) {
            printf("scanf failed\n");
            exit(-1);
        }
        insert_trace(trace_addr);
        for (int i = 0; i < 100; i++) {
            usleep(250000);
            if (uram_read(0x69) != 0xd00df00d) {
                printf("\nrip: 0x%016lx\n", uram_read(0x69));
                return 0;
            }
            printf(".");
        }
        printf("\nPath not hit\n");
    }
        
    if (argv[1][0] == 'c') { // Patch cpuid
        do_cpuid_patch();

        cpuinfo_res result = cpuinfo(0x80000002);
	    printf("cpuinfo: %08x %08x %08x %08x\n", result.rax, result.rbx, result.rcx, result.rdx);
    }
    
    if (argv[1][0] == 'd') { // Dump array
        if (argc < 4) {
            printf("Missing array index\n");
            exit(-1);
        }
        u8 array_idx = argv[3][0] - '0';
        if (array_idx == 0) {
            ms_rom_dump();
        } else if (array_idx == 1) {
            ms_irom_dump();
        } else if (array_idx == 2) {
            ms_patch_consts_dump();
        } else if (array_idx == 3) {
            ms_match_patch_regs_dump();
        } else if (array_idx == 4) {
            ms_patch_ram_dump();
        } else {
            printf("Invalid array index\n");
        }
    }
}
