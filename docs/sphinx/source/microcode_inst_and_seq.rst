Microcode Operations and Sequence Word
======================================

Microcode has a lot of similarities with x86 macro instructions and simpler instructions has an equivalent micro operation.
The most notifiable difference is how its grouped into set of three instructions under control of sequence words.

Microcode Operations
--------------------

Uops varies in amount of operands based on opcode but can also differ from use case to use case. The most simple instruction are moves and ALU operations. In inst.h we have defined
