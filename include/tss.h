// tss.h - Task State Segment

// 1. Load new SS from TSS.ss0
// 2. Load new ESP from TSS.esp0
// 3. Switch to kernel stack
// 4. Push old user state onto kernel stack
// 5. Jump to interrupt handler

#ifndef TSS_H
#define TSS_H

#include <stdint.h>

typedef struct tss_entry {
    uint32_t prev_tss;      // previous TSS link
    uint32_t esp0;          // kernel stack pointer <- the only field we actively use
    uint32_t ss0;           // kernel stack segment <- loaded with 0x10 (kernel data)

    uint32_t esp1;          // ring-1 stack (unused)
    uint32_t ss1;

    uint32_t esp2;          // ring-2 stack (unused)
    uint32_t ss2;

    uint32_t cr3;           // page directory (manage CR3, unused here)

    uint32_t eip;                       // hardware task switching saves full CPU state (unused)
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;

    uint32_t ldt;           // LDT segment selector (unused)
    uint16_t trap;          // debug trap flag
    uint16_t iomap_base;    // I/O permission bitmap offset (point past end = deny all)
} __attribute__((packed)) tss_entry_t;

// called before sched_init().  Zeroes the TSS, fills ss0/esp0,
// install it into GDT[5], re-flushe GDTR, execute ltr 0x28.
void tss_init(void);

// update TSS.esp0 to new process kernel stack top.
// called by the scheduler on every context switch.
void tss_set_esp0(uint32_t esp0);

#endif