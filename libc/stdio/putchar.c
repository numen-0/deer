#include <stdio.h>

    #include <kernel/drivers/vga_screen.h>
#if defined(__is_libk)
    #include <kernel/drivers/vga_screen.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
    vga_putc((char) ic);
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
