#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

#define EOF          (-1)

__BEGIN_DECLS

int printf(const char* __restrict str, ...);
int putchar(int);
int puts(const char* str);

__END_DECLS

#endif
