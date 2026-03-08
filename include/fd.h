// fd.h - File Descriptor Layer

// sits between syscalls and device/VFS backends

#ifndef FD_H
#define FD_H

#include "vfs.h"
#include <stdint.h>

#define FD_MAX      16          // max open fds per process

// open /dev/stdin, /dev/stdout, /dev/stderr as fd 0, 1, 2
void fd_table_init    (file_t **table);

// close a single descriptor
void fd_close         (file_t **table, int fd);

// vfs_close all open entries (called from proc_exit)
void fd_table_close_all(file_t **table);

// fork: share every open file_t (increments each refcount)
void fd_table_clone   (file_t **src, file_t **dst);

// install a file_t at the lowest free slot; returns fd number or -1
int  fd_install       (file_t **table, file_t *f);

// low-level read/write routed through the fd type
// return bytes transferred, or -1 on error
int fd_read (file_t **table, int fd,       void *buf, uint32_t len);
int fd_write(file_t **table, int fd, const void *buf, uint32_t len);

#endif