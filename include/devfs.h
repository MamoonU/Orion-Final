// devfs.h - Device Node Registration

#ifndef DEVFS_H
#define DEVFS_H

#include "vfs.h"

// create /dev and register all standard devices
void     devfs_init(void);

// pre-resolved device vnodes
vnode_t *devfs_stdin_vnode (void);
vnode_t *devfs_stdout_vnode(void);
vnode_t *devfs_stderr_vnode(void);

#endif