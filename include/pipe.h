// pipe.h - Anonymous Pipe IPC

#ifndef PIPE_H
#define PIPE_H

#include "vfs.h"
#include <stdint.h>

#define PIPE_BUFSZ   4096u                                  // ring-buffer capacity (4096 bytes)

#define PIPE_NO_WAITER  0xFFFFu                             // sentinel: no process currently sleeping on this end

// pipe structure
typedef struct pipe {

    uint8_t  buf[PIPE_BUFSZ];   // ring buffer payload

    uint32_t head;              // index of the next byte to read
    uint32_t count;             // bytes currently buffered

    uint32_t readers;           // open read-end descriptors
    uint32_t writers;           // open write-end descriptors

    // PIDs of processes sleeping on this pipe (PIPE_NO_WAITER = none)
    uint16_t blocked_reader;
    uint16_t blocked_writer;
    
} pipe_t;

// per-vnode wrapper: both ends share one pipe_t but need separate vnodes
typedef struct pipe_end {

    pipe_t  *pipe;              // shared ring buffer
    uint8_t  is_write;          // 0 = read end, 1 = write end

} pipe_end_t;

// create anonymous pipe
int pipe_create(file_t **fd_table, int pipefd[2]);

#endif