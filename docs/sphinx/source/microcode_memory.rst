Microcode Memory Layout
=================================

Microcode instructions are grouped into what we call triads, where each triad contains three microcode operations and with each triad is an associated sequence word.
The microcode address space ranges from 0x0000 to 0x7E00 where each microcode instructions can be addressed individually and we will denote the address of a microcode instruction with a U postfixing a hex number. Though out this documentation we will use a couple abbreviations where the most common once are:

* :abbr:`ucode (microcode)` we will often use u as µ and meaning micro.
* :abbr:`uop (microcode opcode/instruction)` referes to a single microcode operation/instruction.
* :abbr:`seqw (microcode sequence word)` is a microcode sequence word.
* :abbr:`MS (microcode sequencer)` is the `microsequencer <https://en.wikipedia.org/wiki/Microsequencer>`_.
* :abbr:`IP (intellectual property)` Cores are `intellectual property cores <https://en.wikipedia.org/wiki/Semiconductor_intellectual_property_core>`_.
* :abbr:`CRBUS (control register bus)` is the control register bus connecting and storing shared state between :abbr:`IP`'s.

Microcode Address Space
-----------------------

As stated above the address space ranges from U0000 to U7E00 exclusively, where U7C00 and above is writeable expect every third microcode which is a implicit nop instruction. Each triad has an associated sequence word controlling the execution flow of the triad. This means that sequence word dictate's at what address we should continue execution after the current triad as well as synchronization and memory barriers. Sequence word and the implicit nop cannot be addressed from microcode and thereby no valid U address exists for these constructs.

.. list-table:: Microcode Addressing Table
   :widths: 10 10 10 10 10 10
   :header-rows: 1

   * - Uaddr
     - instruction
     - instruction
     - instruction
     - implicit nop
     - sequence word
   * - U0000 RO
     - uop 0
     - uop 1
     - uop 2
     - nop
     - seqw 0
   * - U0004 RO
     - uop 4
     - uop 5
     - uop 6
     - nop
     - seqw 1
   * - U0008 RO
     - uop 8
     - uop 9
     - uop A
     - nop
     - seqw 2
   * - U000C RO
     - uop C
     - uop D
     - uop E
     - nop
     - seqw 3
   * - U0010 RO
     - uop 10
     - uop 11
     - uop 12
     - nop
     - seqw 4
   * - ...
     - ...
     - ...
     - ...
     - ...
     - ...
   * - U7C00 RW
     - uop 7C00
     - uop 7C01
     - uop 7C02
     - nop
     - seqw 1f00
   * - U7C04 RW
     - uop 7C04
     - uop 7C05
     - uop 7C06
     - nop
     - seqw 1f01
   * - U7C08 RW
     - uop 7C08
     - uop 7C09
     - uop 7C0A
     - nop
     - seqw 1f02
   * - U7C0C RW
     - uop 7C0C
     - uop 7C0C
     - uop 7C0C
     - nop
     - seqw 1f03
   * - U7C10 RW
     - uop 7C10
     - uop 7C11
     - uop 7C12
     - nop
     - seqw 1f04
   * - ...
     - ...
     - ...
     - ...
     - ...
     - ...
   * - U7DFC RW
     - uop 7DFC
     - uop 7DFD
     - uop 7DFE
     - nop
     - seqw 1F7F

Microcode Sequencer Arrays
--------------------------

The microcode sequencer utilizes 5 arrays refereed to as ms_array 0 to 4 for storing data determining micro execution. The :abbr:`LDAT IP (Local Direct Access Test IP)` can access these arrays and though the CRBUS we can interact with the LDAT. The LDAT as well as ms_arrays are local to each CPU core and we firmly believe that the CRBUS is only for per CORE communication between units and :abbr:`IOSF (Intel On-Chip System Fabric)` is for more global communication. All ms_arrays can be read and some also writeable, altough when writing some arrays is rearranged upon the following read operations.

ms_array 0
^^^^^^^^^^

ms_array 0 we primary use to dump the read only microcode range U0000 to U7C00 but going beyond seems to reflect changes in ms_array 4 described later. U7E00. Reading an address outside a triad E.g. U0003 will write back zero.


ms_array 1
^^^^^^^^^^

ms_array 1 works like ms_array 0 but instead of uops this array stores sequence words. One difference is that only one unique value for each triad exists. This means that reading address 0 to 3 will yield the same sequence word, and next sequence word will be at address 4.


ms_array 2
^^^^^^^^^^

ms_array 2 is writeable and stores sequence words for the writeable microcode address space. Unlike ms_array 1 this array only contains a single entry per triads. This array will therefor only contain 0x80 entries and each entry is maps to 4 in ms_array 1 and will each determine a sequence word for a triad in the range U7C00 to U7E00.

ms_array 3
^^^^^^^^^^

This array controls match and patch and works very differently from the other and we have dedicated the next section for this array alone.

ms_array 4
^^^^^^^^^^

ms_array 4 contains uops for the writeable address space 0x7C00 - 0x7E00. One should write linear to this array as if they were writing to ms_array 0 with a offset of 0x7C00. When reading this array we have observed a strange behavior we have no explanation for. The array will read back the uops in the first column of instructions in the table above as entries from 0x00 to 0x80. And 0x80 to 0x100 will all be sequential entries in the second column of the table above etc.

Reading and Writing
-------------------

In ldat.h we provide a set of function interacting with the LDAT which includes reading and writing to microsequencer arrays.
When reading and writing to these array we recommend using the designated wrappers for reading specific arrays like :c:func:`ms_ro_code_read()` and :c:func:`ms_ro_code_write()`. If you to interact directly with the LDAT one can use the :c:func:`ldat_array_read()` and :c:func:`ldat_array_write()` but be carefull as multiple operations invloving the LDAT should be preformed atomic by implementing it directly in microcode.

Match and Patch
---------------

Match and patch is the mechanism used to put microcode updates into effect and stored in ms_array 3. ms_array 3 contains 32 entries each of witch can redirect any address in the read only address space to an address in writeable address space. Altough we haven't observed index 0 used by any intel provided microcode update it doesn't seam to have any special meaning, and every entry seems to follow the bitfiled pattern described below.

.. bitfield::
    :bits: 31
    :lanes: 1

        [
            { "name": "p",   "bits": 1, "type": 1 },
            { "name": "src",   "bits": 15, "type": 2 },
            { "name": "dst",   "bits": 15, "type": 3 }
        ]

* p
    present flag which dictactes whether the entry is in use.

* src
    15-bit src. This field indicates which address to hook. It is calculated as :math:`\text{src}= \text{uaddr} / 2`

* dst
    15-bit dst. This field indicates which address to jump to. It is calculated as :math:`\text{dst}= \text{uaddr} / 2`

Notice that ``src`` and ``dst`` have no way of encoding an odd U address. We have discovered that this is because every entry in ms_array 3 in fact creates two mappings. One mapping from :math:`\text{src} \Rightarrow \text{dst}` as well as one from :math:`(\text{src}+1) \Rightarrow (\text{dst}+1)`. This can have some consequences on the ability to patch certain addresses as other x86 macro instructions might use :math:`(\text{uaddr}+1)`. When tracing it also makes things harder as for certain cases it can be hard to determine which mapping was in fact causing the jump.

x86 macro instructions seem to each have a fixed U address in the microcode ROM area as an entry point, which we will refer to as xlats. How this mapping from x86 opcodes to xlats is defined is still an open research question. We have included a list of interesting microcode addresses in `labels.txt <https://github.com/zanderdk/lib-micro/blob/master/lables.txt>`_ where most of the opcodes originates from this `list <https://github.com/chip-red-pill/uCodeDisasm/blob/master/glm_ucode_disasm/lables.txt>`_. but due to the discovery of two mappings per entry in match and patch, we have determined that previous ways of tracing has lead to inaccuracies in the list, and we suspect that the updated list still contains errors.
