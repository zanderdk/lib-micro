#!/usr/bin/env python3
import sys

print("/* generated by gen_inst.py */\n")

argdefs = {
    'I0': '#define INSTRNAME_I(imm) ( _INSTRNAME | INSTR_I0(imm)APPEND )',
    'I1': '#define INSTRNAME_I(imm) ( _INSTRNAME | INSTR_I1(imm)APPEND )',
    'R0': '#define INSTRNAME_R(src) ( _INSTRNAME | INSTR_R0(src)APPEND )',
    'R1': '#define INSTRNAME_R(src) ( _INSTRNAME | INSTR_R1(src)APPEND )',
    'M0': '#define INSTRNAME_M(macro) ( _INSTRNAME | INSTR_M0(macro)APPEND )',
    'M1': '#define INSTRNAME_M(macro) ( _INSTRNAME | INSTR_M1(macro)APPEND )',
    'DI0': '#define INSTRNAME_DI(dst, imm) ( _INSTRNAME | INSTR_DI0(dst, imm)APPEND )',
    'DI1': '#define INSTRNAME_DI(dst, imm) ( _INSTRNAME | INSTR_DI1(dst, imm)APPEND )',
    'DR0': '#define INSTRNAME_DR(dst, src) ( _INSTRNAME | INSTR_DR0(dst, src)APPEND )',
    'DR1': '#define INSTRNAME_DR(dst, src) ( _INSTRNAME | INSTR_DR1(dst, src)APPEND )',
    'DM0': '#define INSTRNAME_DM(dst, macro) ( _INSTRNAME | INSTR_DM0(dst, macro)APPEND )',
    'DM1': '#define INSTRNAME_DM(dst, macro) ( _INSTRNAME | INSTR_DM1(dst, macro)APPEND )',
    'RI': '#define INSTRNAME_RI(src, imm) ( _INSTRNAME | INSTR_RI(src, imm)APPEND )',
    'IR': '#define INSTRNAME_IR(imm, src) ( _INSTRNAME | INSTR_IR(imm, src)APPEND )',
    'RM': '#define INSTRNAME_RM(src, macro) ( _INSTRNAME | INSTR_RM(src, macro)APPEND )',
    'MR': '#define INSTRNAME_MR(macro, src) ( _INSTRNAME | INSTR_MR(macro, src)APPEND )',
    'RR': '#define INSTRNAME_RR(src0, src1) ( _INSTRNAME | INSTR_RR(src0, src1)APPEND )',
    'DRI': '#define INSTRNAME_DRI(dst, src, imm) ( _INSTRNAME | INSTR_DRI(dst, src, imm)APPEND )',
    'DIR': '#define INSTRNAME_DIR(dst, imm, src) ( _INSTRNAME | INSTR_DIR(dst, imm, src)APPEND )',
    'DRM': '#define INSTRNAME_DRM(dst, src, macro) ( _INSTRNAME | INSTR_DRM(dst, src, macro)APPEND )',
    'DMR': '#define INSTRNAME_DMR(dst, macro, src) ( _INSTRNAME | INSTR_DMR(dst, macro, src)APPEND )',
    'DRR': '#define INSTRNAME_DRR(dst, src0, src1) ( _INSTRNAME | INSTR_DRR(dst, src0, src1)APPEND )',
}
dsizes = [8, 16, 32, 64]
conditions = ["CONDO", "CONDNO", "CONDB", "CONDNB", "CONDZ", "CONDNZ", "CONDBE", "CONDNBE", "CONDS", "CONDNS", "CONDP", "CONDNP", "CONDL", "CONDNL", "CONDLE", "CONDNLE"]

instructions = [
    {
        'name': 'UJMP',
        'args': ['I1', 'R1'],
    },
    {
        'name': 'MOVE',
        'dsz': True,
        'args': ['DR0', 'DI0', 'DM0'],
    },
    {
        'name': 'ZEROEXT',
        'dsz': True,
        'args': ['DR0', 'DI0', 'DM0'],
    },
    {
        'name': 'MOVETOCREG',
        'dsz': True,
        'append': 'MOD2',
        'args': ['RI', 'RR'],
    },
    {
        'name': 'MOVEFROMCREG',
        'dsz': True,
        'append': 'MOD2',
        'args': ['DI1', 'DR1'],
    },
    {
        'name': 'WRITEURAM',
        'append': 'MOD2',
        'args': ['RI', 'RR'],
    },
    {
        'name': 'READURAM',
        'append': 'MOD2',
        'args': ['DI1', 'DR1'],
    },
    {
        'name': 'MSR2CR',
        'args': ['DR1', 'DI1'],
    },
    {
        'name': 'WRMSLOOPCTRFBR',
        'args': ['R1', 'I1'],
    },
    {
        'name': 'GENARITHFLAGS',
        'append': 'MOD2',
        'args': ['R0', 'RR', 'IR'],
    },
    {
        'name': 'SIGEVENT',
        'args': ['I1', 'RI', 'DI1', 'DRI', 'IR', 'DIR'],
    },
    {
        'name': 'READAFLAGS',
        'append': 'MOD2',
        'args': ['DR1'],
    },
    {
        'name': 'FPREADROM_DTYPENOP',
        'args': ['DR0'],
    },
    {
        'name': 'ADD',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'OR',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'AND',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'SUB',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'SUBR',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'XOR',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'NOTAND',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'ROL',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'ROR',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'RAS',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'SHL',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'SHR',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'CONCAT',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'MOVEINSERTFLGS',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'MOVEMERGEFLGS',
        'dsz': True,
        'args': ['DRI', 'DIR', 'DRM', 'DMR', 'DRR'],
    },
    {
        'name': 'UJMPCC_DIRECT_NOTTAKEN',
        'cond': True,
        'args': ['RI', 'RR'],
    },
    {
        'name': 'MJMPCC_DSZNOP',
        'cond': True,
        'args': ['RI', 'RR'],
    },
    {
        'name': 'SETCC',
        'cond': True,
        'args': ['DR0'],
    },
    {
        'name': 'CMOVCC',
        'dsz': True,
        'cond': True,
        'args': ['DRI', 'DRR'],
    },
    {
        'name': 'SELECTCC',
        'dsz': True,
        'cond': True,
        'args': ['DRI', 'DRR'],
    }
]

def add_args(inst, name):
    for arg in inst['args']:
        if arg not in argdefs:
            print(f'Invalid arg "{arg}"', file=sys.stderr)
            continue
        append = ''
        if 'append' in inst:
            append = ' | ' + inst['append']
        print(argdefs[arg].replace("INSTRNAME", name).replace('APPEND', append))

def add_cond(inst, name):
    if inst.get('cond'):
        for i in conditions:
            add_args(inst, name + '_{}'.format(i))
    else:
        add_args(inst, name)

def add_sc(inst, name):
    if inst.get('sc'):
        for i in inst['sc']:
            add_cond(inst, name + '_SC{}'.format(i))
    else:
        add_cond(inst, name)

def add_asz(inst, name):
    if inst.get('asz'):
        for i in inst['asz']:
            add_sc(inst, name + '_ASZ{}'.format(i))
    else:
        add_sc(inst, name)

def add_dsz(inst, name):
    if inst.get('dsz'):
        for i in dsizes:
            add_asz(inst, name + '_DSZ{}'.format(i))
    else:
        add_asz(inst, name)

for inst in instructions:
    add_dsz(inst, inst['name'])
    print()
