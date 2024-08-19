
#include <stdint.h>
#include <string.h>

extern int    memcmp(const void* s0, const void* s1, size_t n);
extern void*  memcpy(void* __restrict dest, const void* __restrict src, size_t n);
extern void*  memmove(void* dest, const void* src, size_t n);
extern void*  memset(void *s, int c, size_t n);

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
	uint8_t* buf8 = (uint8_t*)s;
    uint8_t  v8   = (uint8_t)value;
    // align buf to 32
    while ( n-- > 0 && ((unsigned int)buf8 & 0x1f) ) { *(buf8++) = v8; }
    int m = n & 0x1f;
    // aligned memset
	uint32_t* buf32 = (uint32_t*)buf8;
    uint32_t  v32   = ((uint32_t)v8 << 24) + ((uint32_t)v8 << 16) +
                      ((uint32_t)v8 << 8)  + (uint32_t)v8;
    n = n >> 5;
    while ( n-- ) {
        // todo: sse2 when available
        *(buf32++) = v32;
    }
    buf8 = (uint8_t*)buf32;
    // finish
    while ( m-- ) {
        *(buf8++) = v8;
    }
	return s;
}
// void* memset(void* s, int value, size_t n) {
// 	uint8_t* buf = (uint8_t*)s;
// 	for ( size_t i = 0; i < n; i++ )
// 		buf[i] = (unsigned char) value;
// 	return s;
// }
