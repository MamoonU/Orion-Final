#ifndef
#define SYSCALL_H


static inline int write(int fd, const void *buf, uint32_t len)
static inline int read(int fd, void *buf, uint32_t len)   
static inline int fork(uint32_t entry)                   
static inline int execve(const char *path)            
static inline int wait(int pid, int *code)              
static inline void exit(int code)  

#endif