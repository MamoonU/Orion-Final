// exec.c - proc_exec

#include "proc.h"
#include "sched.h"
#include "kprintf.h"

// replace program of existing process
int proc_exec(pcb_t *p, uint32_t new_entry) {

    // cant exec null PCB
    if (!p) {
        kprintf("PROC: proc_exec — NULL pcb\n");
        return -1;
    }

    // cant exec running process
    if (p->state == PROC_RUNNING) {
        kprintf("PROC: proc_exec — cannot exec a RUNNING process\n");
        return -1;
    }

    kprintf("PROC: proc_exec — [%u] \"%s\" -> new entry 0x%p\n", (uint32_t)p->pid, p->name, new_entry);

    // remove from ready queue if already queued
    sched_remove(p);

    // re-initialise kernel stack frame at new entry point
    proc_init_frame(p, new_entry);

    // reset accounting and re-arm full timeslice
    p->ticks_total     = 0;
    p->ticks_scheduled = 0;
    p->timeslice       = p->timeslice_len;
    p->wakeup_tick     = 0;
    p->waiting         = 0;

    p->state = PROC_READY;                                              // mark process ready again
    sched_add(p);                                                       // add back to scheduler

    kprintf("PROC: proc_exec — [%u] re-queued at 0x%p\n", (uint32_t)p->pid, new_entry);

    return 0;                                                           // return success
}