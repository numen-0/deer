
#include <stdint.h>
#include <string.h>

extern size_t strlen(const char* str);
extern int    strcmp(const char *s0, const char *s1);

///////////////////////////////////////////////////////////////////////////////
size_t strlen(const char* str) {
	size_t len = 0;
	while ( str[len] ) len++;
	return len;
}
int strcmp(const char *s0, const char *s1) {
    if ( s0 == s1 ) return 0;

    size_t i;
	for ( i = 0; s0[i] == s1[i] && s0[i] != 0; i++) {}

    return s0[i] - s1[i];
}
