#define _GNU_SOURCE

#include <argp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "misc.h"
#include "ldat.h"
#include "patch.h"

#include "ucode_macro.h"

u8 verbose = 0;

const char *argp_program_version = "custom-cpu v0.1";
static char doc[] = "Tool for patching ucode";
static char args_doc[] = "";

// cli argument availble options.
static struct argp_option options[] = {
    {.name="verbose", .key='v', .arg=NULL, .flags=0, .doc="Produce verbose output"},
    {.name="reset", .key='r', .arg=NULL, .flags=0, .doc="reset match & patch"},
    {.name="syscall", .key='s', .arg=NULL, .flags=0, .doc="patch syscall"},
    {.name="core", .key='c', .arg="core", .flags=0, .doc="core to patch [0-3]"},
    {0}
};


// define a struct to hold the arguments.
struct arguments{
    u8 verbose;
    u8 reset;
    u8 syscall;
    s8 core;
};


// define a function which will parse the args.
static error_t parse_opt(int key, char *arg, struct argp_state *state){
    char *token;
    int i;
    struct arguments *arguments = state->input;
    switch(key){

        case 'v':
            arguments->verbose = 1;
            break;
        case 'r':
            arguments->reset = 1;
            break;
        case 's':
            arguments->syscall = 1;
            break;
        case 'c':
            arguments->core = strtol(arg, NULL, 0);
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

void do_syscall_patch() {
    #include "ucode/syscall.h"
    if (verbose)
        print_patch(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    patch_ucode(addr, ucode_patch, ARRAY_SZ(ucode_patch));
    hook_match_and_patch(0x12, hook_address, addr);
    hook_match_and_patch(0x13, 0x02e4, addr+0x24);
}

// initialize the argp struct. Which will be used to parse and use the args.
static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

int main(int argc, char* argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    struct arguments arguments;
    memset(&arguments, 0, sizeof(struct arguments));
    arguments.core = -1;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    verbose = arguments.verbose;

    u8 core = (arguments.core < 0)? 0 : arguments.core;
    if (0 <= core && core <= 3) 
        assign_to_core(core);
    else {
        printf("core out of bound");
        exit(EXIT_FAILURE);
    }

    if (arguments.reset) { // Reset match and patch
        init_match_and_patch();
        usleep(20000);
    }

    if (arguments.syscall) { // Reset match and patch
        do_fix_IN_patch();
        do_syscall_patch();
    }

    return 0;
}
