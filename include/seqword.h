
#define SEQ_UP0(u)      ( ((u) & 0b11) << 0 )
#define SEQ_UP1(u)      ( ((u) & 0b11) << 6 )
#define SEQ_UP2(u)      ( ((u) & 0b11) << 23 )

#define SEQ_EFLOW(x)    ( ((x) & 0b1111) << 2 )
#define SEQ_UADDR(addr) ( ((addr) & 0x7fffUL) << 8 )
#define SEQ_SYNC(x)     ( ((x) & 0b111) << 25 )

// idx controls which uop in triad to target

#define SEQ_URET0(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0x2) )
#define SEQ_URET1(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0x3) )
#define SEQ_SAVEUIP0(idx)           ( SEQ_UP0(idx) | SEQ_EFLOW(0x4) )
#define SEQ_SAVEUIP1(idx)           ( SEQ_UP0(idx) | SEQ_EFLOW(0x5) )
#define SEQ_SAVEUIP0_REGOVR(idx)    ( SEQ_UP0(idx) | SEQ_EFLOW(0x6) )
#define SEQ_SAVEUIP1_REGOVR(idx)    ( SEQ_UP0(idx) | SEQ_EFLOW(0x7) )
#define SEQ_WRTAGW(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0x8) )
#define SEQ_MSLOOP(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0x9) )
#define SEQ_MSSTOP(idx)             ( SEQ_UP0(idx) | SEQ_EFLOW(0xb) )
#define SEQ_UEND0(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xc) )
#define SEQ_UEND1(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xd) )
#define SEQ_UEND2(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xe) )
#define SEQ_UEND3(idx)              ( SEQ_UP0(idx) | SEQ_EFLOW(0xf) )

#define SEQ_GOTO0(addr)     ( SEQ_UP1(0) | SEQ_UADDR(addr) )
#define SEQ_GOTO1(addr)     ( SEQ_UP1(1) | SEQ_UADDR(addr) )
#define SEQ_GOTO2(addr)     ( SEQ_UP1(2) | SEQ_UADDR(addr) )

#define SEQ_LFNCEWAIT(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(1) )
#define SEQ_LFNCEMARK(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(2) )
#define SEQ_LFNCEWTMRK(idx) ( SEQ_UP2(idx) | SEQ_SYNC(3) )
#define SEQ_SYNCFULL(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(4) )
#define SEQ_SYNCWAIT(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(5) )
#define SEQ_SYNCMARK(idx)   ( SEQ_UP2(idx) | SEQ_SYNC(6) )
#define SEQ_SYNCWTMRK(idx)  ( SEQ_UP2(idx) | SEQ_SYNC(7) )

// shortcuts
#define SEQ_NOP     0
#define SEQ_NEXT    SEQ_UP1(3)
#define SEQ_NOSYNC  SEQ_UP2(3)

#define NOP_SEQWORD ( SEQ_NOP | SEQ_NEXT | SEQ_NOSYNC )
#define END_SEQWORD ( SEQ_UEND0(2) | SEQ_NEXT | SEQ_LFNCEWAIT(2) )
