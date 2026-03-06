// syscall.h - System Call Interface

#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>
#include "irq.h"

// syscall numbers
#define SYS_YIELD       0       //                          - yield CPU voluntarily
#define SYS_EXIT        1       // EBX = exit code          - terminate calling process
#define SYS_GETPID      2       //                          - return calling process PID
#define SYS_SLEEP       3       // EBX = ticks              - sleep for N timer ticks
#define SYS_FORK        4       // EBX = child entry point  - spawn child process
#define SYS_EXEC        5       // EBX = pid, ECX = entry   - replace process entry point
#define SYS_WRITE       6       // EBX = const char *msg    - write string to VGA

#define SYSCALL_COUNT   7

// kernel-side entry point (registered in IDT as int 0x80)
void syscall_dispatch(regs_t *r);

// register syscall handler in idt
void syscall_init(void);

#endif