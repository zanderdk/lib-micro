About Lib-Micro
=================================

Lib-Micro is a library that allows you to make apply change to `microcode <https://en.wikipedia.org/wiki/Microcode>`_ from a Linux executable ELF binary.
This library provides a EBPF inspired C styled macro language to chain micro operation and applying patches to the individual CPU cores.
This allow users to change, modify and add functionality to the x86 instruction set.

This library utilizes two
`undocumented instructions <https://github.com/chip-red-pill/udbgInstr/blob/main/paper/undocumented_x86_insts_for_uarch_control.pdf>`_
to do various operations on the micro architectural level such as reading and writing to the microcode rom and ram as well as control register bus etc.

These instructions called ``udbgrd`` and ``udbgwr`` are read and write instructions for Intel engineers to inspect and test changes at lowest level. These instructions requires a Red/Intel unlocked CPU which is currently only achievable on the Goldmount series. We provide a SPI flash `image <http://link-shit-here>`_ with Coreboot and a exploit for `intel-sa-00086 <https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00086.html>`_ providing Red unlock.
