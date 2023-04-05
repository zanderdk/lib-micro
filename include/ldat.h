#ifndef LDAT_H_
#define LDAT_H_
#include "misc.h"
#include "udbg.h"

void ldat_array_write(u64 pdat_reg, u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val);

/**
 * Write a single value from a microsequencer array.
 *
 * @param array_sel: The array index to read.
 * @param bank_sel: Should be 0 for all ms array read/write operations as only a single bank exists.
 * @param dword_idx: Should be 0 for same reasons as bank_sel.
 * @param fast_addr: the address to write to.
 * @param val: The vaule to write.
 */
void ms_array_write(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr, u64 val);


/**
 * Read a single value from a microsequencer array.
 *
 * @param array_sel: The array index to read.
 * @param bank_sel: Should be 0 for all ms array read/write operations as only a single bank exists.
 * @param dword_idx: Should be 0 for same reasons as bank_sel.
 * @param fast_addr: The address to read from.
 *
 * @return A value read from the specified ms_array index and address.
 */
u64 ms_array_read(u64 array_sel, u64 bank_sel, u64 dword_idx, u64 fast_addr);

//read only:
//array0 = ro code
//array1 = ro sequence word

//writeable:
//array2 = wr sequence word
//array3 = match and patch
//array4 = rw code
/**
 * Read a single value from ms_array 0.
 * @param addr: The address to read from.
 *
 * This function is a wrapper around ms_array_read.
 *
 * @return The vaule read from microsequencer.
 */
u64 static ms_array_0_read(u64 addr) {return ms_array_read(0, 0, 0, addr); }

/**
 * Read a single value from ms_array 1.
 * @param addr: The address to read from.
 *
 * This function is a wrapper around ms_array_read.
 *
 * @return The vaule read from microsequencer.
 */
u64 static ms_array_1_read(u64 addr) {return ms_array_read(1, 0, 0, addr); }

/**
 * Read a single value from ms_array 2.
 * @param addr: The address to read from.
 *
 * This function is a wrapper around ms_array_read.
 *
 * @return The vaule read from microsequencer.
 */
u64 static ms_array_2_read(u64 addr) {return ms_array_read(2, 0, 0, addr); }

/**
 * Read a single value from ms_array 3.
 * @param addr: The address to read from.
 *
 * This function is a wrapper around ms_array_read.
 *
 * @return The vaule read from microsequencer.
 */
u64 static ms_array_3_read(u64 addr) {return ms_array_read(3, 0, 0, addr); }

/**
 * Read a single value from ms_array 4.
 * @param addr: The address to read from.
 *
 * This function is a wrapper around ms_array_read.
 *
 * @return The vaule read from microsequencer.
 */
u64 static ms_array_4_read(u64 addr) {return ms_array_read(4, 0, 0, addr); }


/**
 * Read a single microcode instruction from read only address space.
 * @param addr: The address to read from.
 *
 * This function is a simple alias for ms_array_0_read.
 *
 * @return The vaule read from microsequencer.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_0_read")))
#endif
u64 ms_ro_code_read(u64 addr);

/**
 * Read a single sequence word from read only address space.
 * @param addr: The address to read from.
 *
 * This function is a simple alias for ms_array_1_read.
 *
 * @return The vaule read from microsequencer.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_1_read")))
#endif
u64 ms_ro_seq_read(u64 addr);

/**
 * Read a single sequence word from read/write address space.
 * @param addr: The address to read from.
 *
 * This function is a simple alias for ms_array_2_read.
 *
 * @return The vaule read from microsequencer.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_2_read")))
#endif
u64 ms_rw_seq_read(u64 addr);

/**
 * Read a single sequence word from match and patch.
 * @param addr: The address to read from.
 *
 * This function is a simple alias for ms_array_3_read.
 *
 * @return The vaule read from microsequencer.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_3_read")))
#endif
u64 ms_match_n_patch_read(u64 addr);

/**
 * Read a single microcode instruction from read/write address space.
 * @param addr: The address to read from.
 *
 * This function is a simple alias for ms_array_4_read.
 *
 * @return The vaule read from microsequencer.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_4_read")))
#endif
u64 ms_rw_code_read(u64 addr);


/**
 * write a single microcode instruction to ms_array 2.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 */
void static ms_array_2_write(u64 addr, u64 val) {return ms_array_write(2, 0, 0, addr, val); }

/**
 * write a single microcode instruction to ms_array 3.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 */
void static ms_array_3_write(u64 addr, u64 val) {return ms_array_write(3, 0, 0, addr, val); }

/**
 * write a single microcode instruction to ms_array 4.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 */
void static ms_array_4_write(u64 addr, u64 val) {return ms_array_write(4, 0, 0, addr, val); }

/**
 * write a single sequence word to the read/write address space.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 *
 * This function is a simple alias for ms_array_2_write.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_2_write")))
#endif
void ms_rw_seq_write(u64 addr, u64 val);

/**
 * write a single entry to match and patch.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 *
 * This function is a simple alias for ms_array_3_write.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_3_write")))
#endif
void ms_match_n_patch_write(u64 addr, u64 val);

/**
 * write a single microcode instruction to the read/write address space.
 * @param addr: The address to write to.
 * @param val: microcode instruction to write as a uint64_t.
 *
 * This function is a simple alias for ms_array_4_write.
 */
#if __GNUC__
__attribute__((weak, alias("ms_array_4_write")))
#endif
void ms_rw_code_write(u64 addr, u64 val);

/**
 * enable match and pach which esetialy enables microcode updates.
 */

#if __GNUC__
__attribute__((always_inline))
#endif
void static inline enable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp & ~1uL);
}

/**
 * disable match and pach which esetialy disables microcode updates.
 */

#if __GNUC__
__attribute__((always_inline))
#endif
void static inline disable_match_and_patch(void) {
    u64 mp = crbus_read(0x692);
    crbus_write(0x692, mp | 1uL);
}

#endif // LDAT_H_
