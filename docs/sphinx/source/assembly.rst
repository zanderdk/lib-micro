Assembling Microcode
====================

This library contains functionality for assembling, patching, and running microcode. We provide a C macro language for assembling microcode in a similar fashion to the Linux EBPF language. Microcode has a lot of similarities with x86 macro instructions and simple macro instructions will yield a single micro operations. Infact only the most complex instruction will is sequenced using the ms rom. In the folling sections we describe how basic operations can be assembled an refer to API docs for more complicated instruction.


Microcode Operations
--------------------

As opposed to x86 all uops has a fixed length of 48 bits and are arranged in sets of three called a triad. Uops varies in amount of operands based on the opcode and the arguments and their types are encoded within the uop it self. Though out this section we will explain micro operations through examples written using the C macro language. For now we will not go into details about the structure and binray format of microcode but :ref:`here <structure>`, you we document our understanding of the microcode structure.


Move instructions
^^^^^^^^^^^^^^^^^
In this example we demonstrate three diffrent variations of move the instructions ``MOVE_DSZ64_DI``, ``MOVE_DSZ32_DR`` and ``ZEROEXT_DSZ64_DI``.
The following microcode will move the immediate value 0x1337 into the lower 32bits of the ``rax`` register also know as ``eax``. Next instruction is equivalent to ``mov ebx, eax`` and last we use ``ZEROEXT_DSZ64_DI`` for moving 0xcafe zero extended into ``rcx``. Last line is the sequence word and we use the short hand C macro ``END_SEQWORD`` for ending the macro instruction.


.. code-block:: c
    :linenos:
    :caption: Example of move instructions

    ucode_t ucode_patch[] = {
        {
            MOVE_DSZ32_DI(RAX, 0x1337),
            MOVE_DSZ32_DR(RBX, RAX),
            ZEROEXT_DSZ64_DI(RCX, 0xcafe),
            END_SEQWORD
        }
    }

We denote all uops with the opcode a underscore followed by the encoding scheme of the instruction, as shown in the example below.
``D`` means destination register, ``R`` a source register and ``I`` for immediate value. As microcode is fixed at 48bit per operation this puts a limit on the size of immediate value and it's only possible to encode 16bit values.
