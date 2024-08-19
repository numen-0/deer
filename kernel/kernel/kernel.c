
#include <stdio.h>
#include <kernel/isr.h>
#include <kernel/drivers/timer.h>
#include <kernel/drivers/vga_screen.h>

void kernel_main() {
    isr_install();
    irq_install();

    vga_clear_screen();
    vga_print_str("hi\n");
    vga_print_str("> ");

    char * str = "'_'";
    for (int i = 0; i < 0x80; i++) {
        if ( i % 10 == 0 ) vga_print_str("\n");
        str[1] = (char)i;
        vga_print_str(str);
    }

    vga_putc('\n');

    printf("test\n");
    printf("\tint: %d, %d, %d, %d;\n", -231, +20, 0, -0);
    printf("\thex: %x;\n", 0xfee1);
    printf("\tstr: %s;\n", "hola");
    printf("\tchar: %c;\n", 'p');
    printf("\tscape: %%;\n");

    while (1) {
        vga_print_str("sleeping 1s ... ");
        sleep(1000);
        vga_print_str("done\n");
    }

    while (1) { /* halt(); */ };
}

