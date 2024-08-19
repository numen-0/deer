#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for ( size_t i = 0; i < length; i++ ) {
		if ( putchar(bytes[i]) == EOF ) { return false; }
    } return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while ( *format != '\0' ) {
		size_t maxrem = INT_MAX - written;

        // print 'norm' chars, until '%'
		if ( format[0] != '%' || format[1] == '%' ) {
			if ( format[0] == '%' ) { format++; }
			size_t amount = 1;
			while ( format[amount] && format[amount] != '%' ) {
				amount++;
			} if ( maxrem < amount ) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if ( !print(format, amount) ) { return -1; }
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

        // TODO: format specifers %3d, %-12s, ...

        switch ( *format ) {
          case '%': { // scape
			format++;
			if ( !print("%", sizeof(char)*1) ) { return -1; }
			written++;
            break;
        } case 'c': { // char
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if ( !maxrem ) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if ( !print(&c, sizeof(c)) ) { return -1; }
			written++;
            break;
        } case 'd': { // int (decimal)
			format++;
			int n = va_arg(parameters, int);
            bool sing;
            // NOTE: int can go from 2B to 4B, the max max_int = 4,294,967,295 
            //       so 9 digits + 1 for the sing (-).
            char int_str[12]; int_str[11] = 0; 

            if ( n < 0 ) {
                sing = true;
                n = -n;
            } else {
                sing = false;
            }

	        size_t len = 0;
            do {
                len++;
                int_str[11-len] = '0' + (n % 10);
                n = n / 10;
            } while ( n != 0 );
            if ( sing ) { len++; int_str[11-len] = '-'; }

	        if ( maxrem < len ) {
	        	// TODO: Set errno to EOVERFLOW.
	        	return -1;
	        }
	        if ( !print(&int_str[11-len], len) ) { return -1; }
	        written += len;
            break;
        } case 'u': { // unsigned int (decimal)
			format++;
			unsigned int n = (unsigned int)va_arg(parameters, int);
            char int_str[11]; int_str[10] = 0; 

	        size_t len = 0;
            do {
                len++;
                int_str[10-len] = '0' + (n % 10);
                n = n / 10;
            } while ( n != 0 );

	        if ( maxrem < len ) {
	        	// TODO: Set errno to EOVERFLOW.
	        	return -1;
	        }
	        if ( !print(&int_str[10-len], len) ) { return -1; }
	        written += len;
            break;
        } case 'o': { // oct
			format++;
			int n = va_arg(parameters, int);
            char *const oct_str = "0................";
	        const size_t len = 17;
	        if ( maxrem < len ) {
	        	// TODO: Set errno to EOVERFLOW.
	        	return -1;
	        }
            for ( int i = 16; i > 1; i-- ) {
                oct_str[i] = '0' + n & 0x07;
                n = n >> 2;
            }
	        if ( !print(oct_str, len) ) { return -1; }
	        written += len;
            break;
        } case 'x': { // hex
			format++;
			int n = va_arg(parameters, int);
            char *const hex_str = "0x........";
	        const size_t len = 10;
	        if ( maxrem < len ) {
	        	// TODO: Set errno to EOVERFLOW.
	        	return -1;
	        }
            for ( int i = 9; i > 1; i-- ) {
                hex_str[i] = n & 0x0f;
                if ( hex_str[i] < 10 )  hex_str[i] += '0';
                else                    hex_str[i] += 'a' - 10;
                n = n >> 4;
            }
	        if ( !print(hex_str, len) ) { return -1; }
	        written += len;
            break;
        } case 's': { // string
	        format++;
	        const char* str = va_arg(parameters, const char*);
	        size_t len = strlen(str);
	        if ( maxrem < len ) {
	        	// TODO: Set errno to EOVERFLOW.
	        	return -1;
	        }
	        if (!print(str, len)) { return -1; }
	        written += len;
            break;
        } default: { // no match print the rest of the string
			format = format_begun_at;
			size_t len = strlen(format);
			if ( maxrem < len ) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if ( !print(format, len) ) { return -1; }
			written += len;
			format  += len;
            break;
       }};
	}
	va_end(parameters);
	return written;
}
