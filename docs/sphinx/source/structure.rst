.. _structure:

uCode structure
=================================

Instruction
-----------

.. bitfield::
    :bits: 48
    :lanes: 2

        [
            { "name": "src0",   "bits": 6, "type": 7 },
            { "name": "src1",   "bits": 6, "type": 4 },
            { "name": "dst/src2",   "bits": 6, "type": 6 },
            { "name": "imm1",   "bits": 5, "type": 2 },
            { "name": "m0",   "bits": 1, "type": 5 },
            { "name": "imm0",   "bits": 8, "type": 2 },
            { "name": "opcode",   "bits": 12, "type": 3 },
            { "name": "m1",   "bits": 1, "type": 5 },
            { "name": "m2",   "bits": 1, "type": 5 },
            { "name": "crc",   "bits": 2, "type": 1 }
        ]

* opcode
    | A 12-bit opcode value. For some uops, additional information is encoded in the opcode. 
    | For example, in ``CMOVCC``, DSZ and condition are encoded as below:

    .. bitfield::
        :bits: 12
        :lanes: 1

            [
                { "name": "COND",   "bits": 2, "type": 6 },
                { "bits": 4 },
                { "name": "DSZ",   "bits": 2, "type": 3 },
                { "name": "COND",   "bits": 2, "type": 6 },
                { "bits": 2 }
            ]

* src0/src1
    | 6-bit fields that specify which register to get input from.
    | If the uppermost 3 bits equal 0b001, combine imm0, imm1, and src[0:2] to create a 16-bit immediate.
    | If the uppermost 3 bits equal 0b010, combine imm0 and imm1 as an index into constants ROM.
* dst/src2
    | 6-bit field that specifies register to send the output of the operation to.
    | For some memory-related uops, used as a src register instead.
* imm0/imm1
    | In most uops, used as a 16-bit immediate value in src as specified above. 
    | In some uops, e.g. in memory operations, imm0 and imm1 are used as two separate immediates by the instruction.
* m0/m1/m2
    | Several bits that change the mode of uops. 
    | For most operations, m0 means that the immediate value should be interpreted as a macro immediate. 
    | For TESTUSTATE/UPDATEUSTATE m0 is used to invert the operation.
* crc
    2-bit crc. The first bit is the xor of all even-indexed bits. The second bit is the xor of all odd-indexed bits.

Sequence Word
-------------

.. bitfield::
    :bits: 30
    :lanes: 1

        [
            { "name": "up0",   "bits": 2, "type": 4 },
            { "name": "eflow",   "bits": 4, "type": 4 },
            { "name": "up1",   "bits": 2, "type": 2 },
            { "name": "uaddr",   "bits": 15, "type": 2 },
            { "name": "up2",   "bits": 2, "type": 7 },
            { "name": "sync",   "bits": 3, "type": 7 },
            { "name": "crc",   "bits": 2, "type": 1 }
        ]

* up0/up1/up2
    2-bit pointers to uop in triad to perform operation on. See operations below. For up1 and up2, the value 3 specifies NOP

* 0 eflow
    | A 4-bit enum which specifies which eflow operation to run. 
    | The operation is run after the uop pointed to by up0 has been run.

    * 0. NOP
    * 2. URET0
    * 3. URET1
    * 4. SAVEUIP0
    * 5. SAVEUIP1
    * 6. SAVEUIP0_REGOVR
    * 7. SAVEUIP1_REGOVR
    * 8. WRTAGW
    * 9. MSLOOP
    * b. MSSTOP
    * c. UEND0
    * d. UEND1
    * e. UEND2
    * f. UEND3

* 1 uaddr
    | Address to jump to after uop pointed to by up1 has been run. If up1=3, this is ignored.
    | This is always run after eflow if up0=up1.
    | This is turned into a conditional jump if preceded by ``TESTUSTATE`` or ``SUBR``.

* 2 sync
    | A 3-bit enum that specifies synchronization of the operation. For example load fences and synchronization barriers.
    | Synchronization is performed on the uop pointed by up2 and ignored if up2=3.

    * 1. LFNCEWAIT
    * 2. LFNCEMARK
    * 3. LFNCEWTMRK
    * 4. SYNCFULL
    * 5. SYNCWAIT
    * 6. SYNCMARK
    * 7. SYNCWTMRK
* crc
    2-bit crc. The first bit is the xor of all even-indexed bits. The second bit is the xor of all odd-indexed bits.
