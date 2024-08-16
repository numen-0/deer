
#include <ctype.h>

#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/vga_screen.h>
#include <kernel/io.h>

extern void in_keyboard(key_info key);
extern void out_print(char* str);

void bytetohex(unsigned char b, char* buff) {
    buff[0] = b / 16 + '0';
    buff[1] = b % 16 + '0';
    if ( buff[0] > '9' ) buff[0] += 'a' - '9' - 1;
    if ( buff[1] > '9' ) buff[1] += 'a' - '9' - 1;
}
void in_keyboard(key_info key) {
    if ( key.kc == K_UNKW || (key.kf & K_FLAG_KEYUP) ) return;

    if ( !isprint(key.rep) ) return;

    // char hex[] = "0x00";
    // bytetohex(key.kf, hex + 2);
    // vga_print_at(hex, 0, 0);

    vga_putc(key.rep);
    // vga_putc('\n');
}
