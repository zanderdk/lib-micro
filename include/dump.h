#ifndef DUMP_H_
#define DUMP_H_
#include "misc.h"

void ms_array_dump(u64 array_sel, u64 fast_addr, u64 size);
void ms_ro_code_dump(void);
void ms_ro_seqw_dump(void);
void ms_rw_seqw_dump(void);
void ms_match_n_patch_dump(void);
void ms_rw_code_dump(void);
void uram_dump(void);

#endif // DUMP_H_
