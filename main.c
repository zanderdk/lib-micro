#define _GNU_SOURCE

#include "main.h"
#include<argp.h>
#include <string.h>

#include "opcode.h"
#include "ucode_macro.h"

u8 verbose = 0;

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
    if (verbose)
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
    if (verbose)
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
    if (verbose)
        printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    hook_match_and_patch(0x1f, hook_address, addr);
}

void do_cpuid_patch() {
    #include "ucode/cpuid.h"
    if (verbose)
        printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    hook_match_and_patch(0, hook_address, addr);
}

void install_jump_target(u64 uaddr) {
    #include "ucode/jump_target.h"
    staging_write(0xba40, uaddr);
    staging_write(0xba80, 0xcafebabe);
    if (verbose)
        printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    if (verbose)
        printf("jump_target return value: 0x%lx\n", ucode_invoke(0x7d00));
}

void persistent_trace(u64 hook_address) {
    install_jump_target(hook_address);
    u64 uop0 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+0) & CRC_UOP_MASK;
    u64 uop1 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+1) & CRC_UOP_MASK;
    u64 uop2 = ldat_array_read(0x6a0, 0, 0, 0, hook_address+2) & CRC_UOP_MASK;
    u64 seq =  ldat_array_read(0x6a0, 1, 0, 0, hook_address) & CRC_SEQ_MASK; //sequence word

    uop0 = CRC_UOP(uop0);
    uop1 = CRC_UOP(uop1);
    uop2 = CRC_UOP(uop2);
    seq = CRC_SEQ(seq);

    if (verbose) {
        printf("uop0: 0x%012lx\n", uop0);
        printf("uop1: 0x%012lx\n", uop1);
        printf("uop2: 0x%012lx\n", uop2);
        printf("seq: 0x%012lx\n", seq);
    }
    /* #include "ucode/persistent_trace.h" */

    unsigned long addr = 0x7c10;
    unsigned long ucode_patch[][4] = {
        // U7c10: WRITEURAM(tmp0, 0x01a0, 64); tmp0:= MOVE_DSZ64(0xdead); tmp0:= SHL_DSZ64(tmp0, 0x10)
        {0x8043a0040230, 0x8049ad7b000e, 0x406410030230, 0x300000c0},
        // U7c14: tmp0:= OR_DSZ64(tmp0, 0xdead); tmp0:= SHL_DSZ64(tmp0, 0x10); tmp0:= OR_DSZ64(tmp0, 0xdead)
        {0xc041ad7b03b0, 0x406410030230, 0xc041ad7b03b0, 0x300000c0},
        // U7c18: tmp0:= SHL_DSZ64(tmp0, 0x10); tmp0:= OR_DSZ64(tmp0, 0xdead); tmp0:= XOR_DSZ64(tmp0, rax)
        {0x406410030230, 0xc041ad7b03b0, 0x4600030830, 0x300000c0},
        // U7c1c: UJMPCC_DIRECT_NOTTAKEN_CONDZ(tmp0, 0x7d00); tmp0:= READURAM( , 0x01a0, 64); NOP
        {0x150007402f0, 0x63a0070200, 0x0, 0x300000c0},
        // U7c20: orig uops
        {uop0, uop1, uop2, seq},
        // U7c24: UJMP(, hook_address); NOP; NOP
        {UJMP(hook_address+4), 0x0, 0x0, 0x300000c0}
    };

    if (verbose) {
        for (u64 i = 0; i < sizeof(ucode_patch) / sizeof(ucode_patch[0]); i++) {
            printf("%04lx: %012lx %012lx %012lx %012lx\n", i, ucode_patch[i][0], ucode_patch[i][1], ucode_patch[i][2], ucode_patch[i][3]);
        }
    }

    if (verbose)
        printf("patching addr: %08lx - ram: %08lx\n", addr, ucode_addr_to_patch_addr(addr));
    patch_ucode(addr, ucode_patch, sizeof(ucode_patch) / sizeof(ucode_patch[0]));
    hook_match_and_patch(0, hook_address, addr);

}

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
        exit(EXIT_FAILURE);
    }
    ucode_patch[n_tetrads-1][3] = seqw_goto;
    if (ucode_patch[n_tetrads-1][0] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][0] = 0;
    if (ucode_patch[n_tetrads-1][1] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][1] = 0;
    if (ucode_patch[n_tetrads-1][2] == END_UNKOWN_UOP) ucode_patch[n_tetrads-1][2] = 0;
    
    patch_ucode(addr, ucode_patch, n_tetrads);
    hook_match_and_patch(0, tracing_addr, addr);   
}


typedef struct {
    u64 rax;
    u64 rbx;
    u64 rcx;
    u64 rdx;
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

const char *argp_program_version = "custom-cpu v0.1";
static char doc[] = "Tool for patching ucode";
static char args_doc[] = "";

// cli argument availble options.
static struct argp_option options[] = {
    {.name="verbose", .key='v', .arg=NULL, .flags=0, .doc="Produce verbose output"},
    {.name="reset", .key='r', .arg=NULL, .flags=0, .doc="reset match & patch"},
    {.name="cpuid", .key='i', .arg=NULL, .flags=0, .doc="patch cpuid"},
    {.name="wait_trace", .key='w', .arg=NULL, .flags=0, .doc="wait for hit on trace"},
    {.name="dump_ram", .key='d', .arg=NULL, .flags=0, .doc="dump uram"},
    {.name="xlat_fuzz", .key='x', .arg=NULL, .flags=0, .doc="start fuzzing xlats"},
    {.name="trace", .key='t', .arg="uaddr", .flags=0, .doc="trace ucode addr"},
    {.name="dump_array", .key='a', .arg="array", .flags=0, .doc="dump array"},
    {.name="core", .key='c', .arg="core", .flags=0, .doc="core to patch [0-3]"},
    {0}
};


// define a struct to hold the arguments.
struct arguments{
    u8 verbose;
    u8 reset;
    u8 uram;
    u8 wait;
    u8 cpuid;
    u8 xlat;
    s32 trace_addr;
    s8 array;
    s8 core;
};


// define a function which will parse the args.
static error_t parse_opt(int key, char *arg, struct argp_state *state){

    struct arguments *arguments = state->input;
    switch(key){

        case 'v':
            arguments->verbose = 1;
            break;
        case 'x':
            arguments->xlat = 1;
            break;
        case 'r':
            arguments->reset = 1;
            break;
        case 'i':
            arguments->cpuid = 1;
            break;
        case 'd':
            arguments->uram = 1;
            break;
        case 'w':
            arguments->wait = 1;
            break;
        case 't':
            arguments->trace_addr = atoi(arg);
            if (arguments->trace_addr < 0){
                argp_usage(state);
                exit(EXIT_FAILURE);
            }
            break;
        case 'a':
            arguments->array = atoi(arg);
            if (arguments->array < 0 || arguments->array > 4){
                argp_usage(state);
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            arguments->core = atoi(arg);
            if (arguments->core < 0 || arguments->core > 3){
                argp_usage(state);
                exit(EXIT_FAILURE);
            }
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

__attribute__((always_inline))
cpuinfo_res static inline try_xlat(u64 val) {
    u64 rax = val;
    cpuinfo_res result;
    lmfence();
    asm volatile(
        "iretq\n\t"
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

void xlat_fuzzing(void) {
    u64 cpuid_xlat = 0x0be0;
    u64 pause_xlat = 0x0bf0;
    u64 iret_xlat = 0x07c8;
    persistent_trace(iret_xlat);
    cpuinfo_res val = try_xlat(0xdeaddeaddeaddeadUL);
    printf("rax:        0x%lx\n", val.rax);
    printf("rbx:        0x%lx\n", val.rbx);
    printf("rcx:        0x%lx\n", val.rcx);
    printf("rbx:        0x%lx\n", val.rdx);
}


// initialize the argp struct. Which will be used to parse and use the args.
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char* argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    struct arguments arguments;
    memset(&arguments, 0, sizeof(struct arguments));
    arguments.trace_addr = -1;
    arguments.array = -1;
    arguments.core = -1;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    verbose = arguments.verbose;

    if (verbose) {
        puts("arguments:");
        printf("\tverbose:       %d\n", arguments.verbose);
        printf("\treset:         %d\n", arguments.reset);
        printf("\tcpuid:         %d\n", arguments.cpuid);
        printf("\txlat:          %d\n", arguments.xlat);
        printf("\ttrace_addr:    0x%x\n", (u32)arguments.trace_addr);
        printf("\twait:          %d\n", arguments.wait);
        printf("\tarray:         %d\n", arguments.array);
        printf("\turam:          %d\n", arguments.uram);
        printf("\tcore:          %d\n", arguments.core);
        puts("");
    }

    u8 core = (arguments.core < 0)? 0 : arguments.core;
    if (0 <= core && core <= 3) 
        assign_to_core(core);
    else {
        printf("core out of bound");
        exit(EXIT_FAILURE);
    }

    if (arguments.reset) { // Reset match and patch
        init_match_and_patch();
        do_fix_IN_patch();
    }

    if (arguments.xlat) {
        xlat_fuzzing();
    }

    if (arguments.trace_addr > -1) { // Do trace
        uram_write(0x69, 0xd00df00d);
        u64 trace_addr = arguments.trace_addr;
        insert_trace(trace_addr);
        if (arguments.wait) {
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
    }
        
    if (arguments.cpuid) { // Patch cpuid
        do_cpuid_patch();

        if (verbose) {
            cpuinfo_res result = cpuinfo(0x80000002);
            printf("cpuinfo: 0x%016lx 0x%016lx 0x%016lx 0x%016lx\n", result.rax, result.rbx, result.rcx, result.rdx);
        }
    }
    
    if (arguments.array > -1) { // Dump array
        u8 array_idx = arguments.array;
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

    if(arguments.uram) {
        uram_dump();
    }

    return 0;
}
