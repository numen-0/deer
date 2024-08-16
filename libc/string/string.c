
#include <string.h>

extern int    memcmp(const void* s0, const void* s1, size_t n);
extern void*  memcpy(void* __restrict dest, const void* __restrict src, size_t n);
extern void*  memmove(void* dest, const void* src, size_t n);
extern void*  memset(void *s, int c, size_t n);

extern size_t strlen(const char* str);
extern int    strcmp(const char *s0, const char *s1);

///////////////////////////////////////////////////////////////////////////////
int memcmp(const void* s0, const void* s1, size_t n) {
    if ( s0 == s1 ) return 0;

	const unsigned char* a = (const unsigned char*) s0;
	const unsigned char* b = (const unsigned char*) s1;

    size_t i;
	for ( i = 0; i < n && a[i] == b[i]; i++) {}

    return (i < n) ? 0 : a[i] - b[i];
}
void* memcpy(void* __restrict dest, const void* __restrict src, size_t n) {
	unsigned char* d = (unsigned char*) dest;
	const unsigned char* s = (const unsigned char*) src;

	for ( size_t i = 0; i < n; i++ )
		d[i] = s[i];
	return dest;
}
void* memmove(void* dest, const void* src, size_t n) {
	unsigned char* d = (unsigned char*) dest;
	const unsigned char* s = (const unsigned char*) src;
	if ( d < s ) {
		for ( size_t i = 0; i < n; i++ )
			d[i] = s[i];
	} else {
		for (size_t i = n; i != 0; i-- )
			d[i-1] = s[i-1];
	}
	return dest;
}
void* memset(void* s, int value, size_t n) {
	unsigned char* buf = (unsigned char*) s;

	for ( size_t i = 0; i < n; i++ )
		buf[i] = (unsigned char) value;
	return s;
}

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
