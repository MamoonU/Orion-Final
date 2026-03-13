// namespace.c - Per-Process Namespace (Plan 9 bind semantics)
 
#include "namespace.h"
#include "vfs.h"
#include "kheap.h"
#include "string.h"
#include "kprintf.h"

// count # binds at path
static uint32_t count_at(const ns_t *ns, const char *new_path) {

    uint32_t n = 0;

    for (uint32_t i = 0; i < NS_BINDS_MAX; i++) {
        if (ns->binds[i].active && strcmp(ns->binds[i].new_path) == 0)
        n++;
    }
    return n;
}

// allocate ns object
ns_t *ns_create(void) {
 
    ns_t *ns = kmalloc(sizeof(ns_t));                               // alloc mem
    if (!ns) {
        kprintf("NS: ns_create — OOM\n");                           // OOM
        return 0;
    }
 
    // initialise fields
    ns->refcount = 1;
    ns->nbinds   = 0;
 
    for (uint32_t i = 0; i < NS_BINDS_MAX; i++) {                   // clear bind table
        ns->binds[i].active = 0;
        ns->binds[i].vnode  = 0;
        ns->binds[i].srv_fd = -1;
    }
    kprintf("NS: created namespace @ 0x%p\n", (uint32_t)ns);
    return ns;
}

// deep copy ns
ns_t *ns_clone(const ns_t *src) {
 
    ns_t *dst = ns_create();                                        // alloc ns
    if (!dst) return 0;
 
    if (!src) return dst;                                           // cloning null = fresh ns
 
    dst->nbinds = src->nbinds;                                      // copy bind count
 
    for (uint32_t i = 0; i < NS_BINDS_MAX; i++) {                   // loop bind table
 
        const ns_bind_entry_t *se = &src->binds[i];
        ns_bind_entry_t       *de = &dst->binds[i];
 
        if (!se->active) {                                          // case 1: entry inactive
            de->active = 0;
            de->vnode  = 0;
            de->srv_fd = -1;
            continue;
        }
 
        strncpy(de->new_path, se->new_path, VFS_PATH_MAX - 1);      // case 2: entry active
        de->new_path[VFS_PATH_MAX - 1] = '\0';
 
        de->vnode  = se->vnode;                                     // copy -> path
        de->flags  = se->flags;                                     // copy -> flags
        de->active = 1;                                             // copy -> vnode-ptr
        de->srv_fd = se->srv_fd;                                    // copy -> srv_fd
 
        if (de->vnode) vnode_ref(de->vnode);                        // vnode_ref
    }
    kprintf("NS: cloned namespace 0x%p -> 0x%p (%u binds)\n", (uint32_t)src, (uint32_t)dst, dst->nbinds);
    return dst;
}

// increment refcount
void  ns_ref  (ns_t *ns) {

}

// decrement refcount (refcount = 0 = free ns)
void  ns_unref(ns_t *ns) {

}

// bind operation
int ns_bind(ns_t **ns, vnode_t *vnode, const char *new_path, uint8_t flags) {

}

// unbind operation
int ns_unbind(ns_t **ns, const char *new_path) {

}

// path resolution 
vnode_t *ns_resolve(ns_t *ns, const char *path) {

}

// handle union directory listing
int ns_readdir(ns_t *ns, const char *dir_path, uint32_t index, char *name_out, uint32_t name_max, vnode_t **node_out) {

}

// debug
void ns_dump(const ns_t *ns) {
    
}