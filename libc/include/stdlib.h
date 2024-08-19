#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

// #define __need_wchar_t
#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// #define	RAND_MAX	2147483647

__BEGIN_DECLS

// typedef struct {
//     int quot;			/* Quotient.  */
//     int rem;			/* Remainder.  */
// } div_t;


// TODO
// /* Converts the string pointed to floating-point number (type double). */
// double atof(const char *str);
// /* Converts the string pointed to an integer (type int). */
// int atoi(const char *str);
// /* Converts the string pointed to a long integer (type long int). */
// long int atol(const char *str);
// /* Converts the string pointed to floating-point number (type double). */
// double strtod(const char *str, char **endptr);
// /* Converts the string pointed to, by the argument str to a long integer (type 
//  * long int). */
// long int strtol(const char *str, char **endptr, int base);
// /* Converts the string pointed to, by the argument str to an unsigned long 
//  * integer (type unsigned long int). */
// unsigned long int strtoul(const char *str, char **endptr, int base);

// Causes an abnormal program termination
__attribute__((__noreturn__)) void abort(void);

/* Deallocates previously allocated memory */
void  free(void* ptr);
/* Allocate SIZE bytes of memory. */
void* malloc(size_t size);
/* Allocate NITEMS elements of SIZE bytes each, all initialized to 0. */
void* calloc(size_t nitems, size_t size);
/* Re-allocate the previously allocated block of SIZE bytes long in PTR */
void* realloc(void* ptr, size_t size);


__END_DECLS

#endif
