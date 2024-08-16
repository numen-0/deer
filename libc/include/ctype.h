
#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

__BEGIN_DECLS

// isalnum(c) || isalpha(c)
extern int isalnum(int c);
// [a-zA-Z]
extern int isalpha(int c);
// ((0 <= c && c <= 31) || c == 127)
extern int iscntrl(int c);
// [0-9]
extern int isdigit(int c);
// isalnum(c) || ispunct(c)
extern int isgraph(int c);
// [a-z]
extern int islower(int c);
// isalnum(c) || ispunct(c) || isspace(c)
extern int isprint(int c);
// !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
extern int ispunct(int c);
// c in {' ', '\n', '\t', '\r', '\v', '\f'}
extern int isspace(int c);
// [A-Z]
extern int isupper(int c);
// [0-9a-fA-F]
extern int isxdigit(int c);
// {' ', '\t'}
extern int isblank(int c);

extern int tolower(int c);
extern int toupper(int c);


__END_DECLS

#endif
