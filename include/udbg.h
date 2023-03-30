#ifndef UDBG_H_
#define UDBG_H_
#include "misc.h"

typedef struct {
    u64 value;
    u64 status;
} u_result_t;

u_result_t udbgrd(uint64_t type, uint64_t addr);

u_result_t udbgwr(uint64_t type, uint64_t addr, uint64_t value);

#define SIMPLERD(name, type) \
u64 static name(u64 addr) { \
    return (u64)udbgrd(type, addr).value; \
}

SIMPLERD(crbus_read, 0x00)
SIMPLERD(uram_read, 0x10)
SIMPLERD(io8_read, 0x18)
SIMPLERD(io16_read, 0x48)
SIMPLERD(io32_read, 0x50)
SIMPLERD(io64_read, 0x58)
SIMPLERD(staging_read, 0x80)
SIMPLERD(staging2_read, 0x40)

#undef SIMPLERD

#define STATUSRD(name, type) \
u_result_t static name(u64 addr) { \
 return udbgrd(type, addr); \
}

STATUSRD(sa_read, 0x08)

#undef STATUSRD

#define SIMPLEWR(name, type)     \
void static name(u64 addr, u64 value) { \
    udbgwr(type, addr, value); \
}

SIMPLEWR(crbus_write, 0x00)
SIMPLEWR(uram_write, 0x10)
SIMPLEWR(io8_write, 0x18)
SIMPLEWR(io16_write, 0x48)
SIMPLEWR(io32_write, 0x50)
SIMPLEWR(io64_write, 0x58)
SIMPLEWR(staging_write, 0x80)
SIMPLEWR(staging2_write, 0x40)

#undef SIMPLEWR

#define RBXWR(name, type) \
u64 static name(u64 addr, u64 value) { \
    return (u64)udbgwr(type, addr, value).status; \
}

RBXWR(sa_write, 0x08)

#undef RBXWR

#define RDXWR(name, type) \
u64 static name(u64 addr, u64 value) { \
    return (u64)udbgwr(type, addr, value).value; \
}

RDXWR(iosf_sb_write, 0xD0)

#undef RDXWR

#endif // UDBG_H_
