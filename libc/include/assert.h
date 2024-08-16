#ifndef _ASSERT_H
#define _ASSERT_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
# define __ASSERT_VOID_CAST static_cast<void>
#else
# define __ASSERT_VOID_CAST (void)
#endif

#ifdef NDEBUG
# define assert(expr)   (__ASSERT_VOID_CAST (0))
#else
__BEGIN_DECLS

/* This prints an "Assertion failed" message and aborts.  */
extern void __assert_fail(const char* assertion, const char* file,
			   unsigned int line, const char* function)
     __attribute__((__noreturn__));

__END_DECLS

#define assert(expr)            \
    ((expr)                     \
     ? __ASSERT_VOID_CAST (0)   \
     : __assert_fail(#expr, __FILE__, __LINE__, __func__))
#endif // NDEBUG

#define static_assert(expr, msg) _Static_assert(expr, msg);

#endif // _ASSERT_H
