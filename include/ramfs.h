// ramfs.h - In-Memory Filesystem

#ifndef RAMFS_H
#define RAMFS_H

#include "vfs.h"

// initialise ramfs and mount it at "/"
void     ramfs_init(void);

// return the root directory vnode
vnode_t *ramfs_get_root(void);

// register already-constructed device vnode at path inside ramfs
int      ramfs_register_dev(const char *path, vnode_t *dev_vnode);

#endif