#define _GNU_SOURCE

#include <argp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "misc.h"
#include "ldat.h"
#include "dump.h"
#include "patch.h"

#include "ucode_macro.h"

const char *argp_program_version = "custom-cpu v0.1";
static char doc[] = "Tool for patching ucode";
static char args_doc[] = "";

// cli argument availble options.
static struct argp_option options[] = {
    {.name="dump_ram", .key='d', .arg=NULL, .flags=0, .doc="dump uram"},
    {.name="dump_array", .key='a', .arg="array", .flags=0, .doc="dump array"},
    {.name="core", .key='c', .arg="core", .flags=0, .doc="core to patch [0-3]"},
    {0}
};


// define a struct to hold the arguments.
struct arguments{
    u8 uram;
    s8 array;
    s8 core;
};


// define a function which will parse the args.
static error_t parse_opt(int key, char *arg, struct argp_state *state){
    char *token;
    int i;
    struct arguments *arguments = state->input;
    switch(key){
        case 'd':
            arguments->uram = 1;
            break;
        case 'a':
            arguments->array = strtol(arg, NULL, 0);
            if (arguments->array < 0 || arguments->array > 4){
                argp_usage(state);
                exit(EXIT_FAILURE);
            }
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


static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char* argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    struct arguments arguments;
    memset(&arguments, 0, sizeof(struct arguments));
    arguments.array = -1;
    arguments.core = -1;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    u8 core = (arguments.core < 0)? 0 : arguments.core;
    if (0 <= core && core <= 3) 
        assign_to_core(core);
    else {
        printf("core out of bound");
        exit(EXIT_FAILURE);
    }

    if (arguments.array > -1) { // Dump array
        u8 array_idx = arguments.array;
        if (array_idx == 0) {
            ms_ro_code_dump();
        } else if (array_idx == 1) {
            ms_ro_seqw_dump();
        } else if (array_idx == 2) {
            ms_match_n_patch_dump();
        } else if (array_idx == 3) {
            ms_match_n_patch_dump();
        } else if (array_idx == 4) {
            ms_rw_code_dump();
        } else {
            printf("Invalid array index\n");
        }
    }

    if(arguments.uram) {
        uram_dump();
    }

    return 0;
}
