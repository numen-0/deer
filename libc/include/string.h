#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

__BEGIN_DECLS

/* Compare N bytes of S0 and S1.  */
extern int memcmp(const void* s0, const void* s1, size_t n);
/* Copy N bytes of SRC to DEST.  */
extern void* memcpy(void* __restrict dest, const void* __restrict src, size_t n);
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void* memmove(void* dest, const void* src, size_t n);
/* Set N bytes of S to C.  */
extern void* memset(void *s, int c, size_t n);

/* Return the length of STR.  */
extern size_t strlen(const char* str);
/* Compare strings S0 and S1.  */
extern int strcmp(const char *s0, const char *s1);

__END_DECLS

#endif
