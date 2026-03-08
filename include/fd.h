// fd.h - File Descriptor Layer

// sits between syscalls and device/VFS backends

#ifndef FD_H
#define FD_H

#include <stdint.h>
#include <stddef.h>

#define FD_MAX      16          // max open fds per process

// fd type tags
#define FD_NONE     0           // slot is free
#define FD_STDIN    1           // keyboard input
#define FD_STDOUT   2           // VGA terminal
#define FD_STDERR   3           // serial port

typedef struct {
    uint8_t  type;              // FD_* tag above
    uint8_t  flags;             // reserved for O_CLOEXEC etc.
} fd_entry_t;


void fd_table_init(fd_entry_t *table);                                      // initialise fd table for a new process (open stdin/stdout/stderr)

void fd_close(fd_entry_t *table, int fd);                                   // close one entry

void fd_table_clone(const fd_entry_t *src, fd_entry_t *dst);                // clone parents fd table into childs (used by proc_fork)

// low-level read/write routed through the fd type
// return bytes transferred, or -1 on error
int fd_read (fd_entry_t *table, int fd,       void *buf, uint32_t len);
int fd_write(fd_entry_t *table, int fd, const void *buf, uint32_t len);

#endif