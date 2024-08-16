#ifndef _IO_H
#define _IO_H

#include <kernel/drivers/keyboard.h>

// NOTE: meybe in a future extend this funct to manage the key input and
//       distribute the key_info to the listeners, for now our only listener is
//       our kernel
extern void in_keyboard(key_info key);

// NOTE: maybe usefull to pass an address and write to the address, so you can
//       have "files" in mem, to edit and stuff.
//       for now just write all to stdout (the vga term)
extern void out_print(char* str);

#endif // _IO_H
