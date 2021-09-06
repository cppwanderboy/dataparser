#ifndef _COMMON_INCLUDE_H_
#define _COMMON_INCLUDE_H_

# define likely(x)  __builtin_expect(!!(x), 1)
# define unlikely(x)    __builtin_expect(!!(x), 0)

#define packed __attribute__((packed))

#endif /**_COMMON_INCLUDE_H_*/