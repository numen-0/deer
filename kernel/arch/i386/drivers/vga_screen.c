// VGA screen driver

#include <string.h>
#include <stdint.h>
#include <kernel/ports.h>
#include <kernel/drivers/vga_screen.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK (VGA_COLOR_BLACK << 4 | VGA_COLOR_WHITE)
#define RED_ON_WHITE 0xf4

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

uint16_t *const vidmem = (uint16_t *) VIDEO_ADDRESS;
vga_16_color vga_color = WHITE_ON_BLACK << 8;
uint32_t offset = 0;

extern void vga_clear_screen(void);
extern void vga_scroll(int lines);
extern void vga_putc(char c);
extern void vga_print_at(const char * str, int col, int row);
extern void vga_print_str(const char * str);
extern void vga_change_color(vga_16_color fg, vga_16_color bg);
extern void vga_change_color_fg(vga_16_color fg);
extern void vga_change_color_bg(vga_16_color bg);

///////////////////////////////////////////////////////////////////////////////
#define get_offset(col, row) (row * MAX_COLS + col)
#define get_row(of)          (of / MAX_COLS)
#define get_col(of)          (of % MAX_COLS)
#define set_col(of, col)     (get_row(of) * MAX_COLS + col)
#define set_row(of, row)     (row * MAX_COLS + of % MAX_COLS)
#define move_newline(of)     ((get_row(of) + 1) * MAX_COLS)
#define move_tab(of)         ((of + 4) & (~0x03))
#define add_col(of, col)     (of + col)
#define add_row(of, row)     (of + row * MAX_COLS)
#define in_bounds(of)        (of <= MAX_COLS * MAX_ROWS)


int vga_get_cursor_offset() {
    // Use the VGA ports to get the current cursor position
    //     1. Ask for high byte of the cursor offset (data 0x0E)
    //     2. Ask for low byte (data 0x0F)
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
    offset = offset + port_byte_in(REG_SCREEN_DATA);
    return offset; /* Position * size of character cell */
}

void vga_set_cursor_offset(uint16_t of) {
    /* Similar to vga_get_cursor_offset, but instead of reading we write data */
    offset = of;
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

// public /////////////////////////////////////////////////////////////////////
void vga_change_color(vga_16_color fg, vga_16_color bg) {
    vga_color = (bg << 4 | fg) << 8;
}
void vga_change_color_fg(vga_16_color fg) {
    vga_color = (vga_color & 0xf000) | (fg << 8);
}
void vga_change_color_bg(vga_16_color bg) {
    vga_color = (vga_color & 0x0f00) | (bg << 8);
}

void vga_scroll(int lines) {
    if ( lines >= MAX_ROWS ) {
        vga_clear_screen();
        return;
    }
    void*  dest = vidmem;
    void*  src  = &vidmem[lines * MAX_COLS];
    size_t n    = (MAX_ROWS - lines) * MAX_COLS * 2;

    memmove(dest, src, n);

    memset(&dest[n], 0, 2*MAX_ROWS*MAX_COLS - n);
    offset = add_row(offset, -lines);
}
void vga_clear_screen() {
    memset(vidmem, 0, 2*MAX_ROWS*MAX_COLS);
    vga_set_cursor_offset(0);
}
void vga_putc(char c) {
    if ( c == '\n' ) {
        offset = move_newline(offset);
    } else if ( c == '\t' ) {
        uint32_t prev_row = get_row(offset);
        offset = move_tab(offset);
        if ( get_row(offset) > prev_row ) {
            offset = set_col(offset, 0);
        }
        return;
    } else if ( c == '\b' ) {
        vidmem[--offset] = 0;
        return;
    } else {
        vidmem[offset++] = vga_color | c;
    }
    vga_set_cursor_offset(offset);
}
void vga_print_str(const char * str) {
    // TODO: test offset stuff
    // int offset = vga_get_cursor_offset();
    int i = 0;

    while ( str[i] ) {
        vga_putc(str[i]); i++;

        if ( !in_bounds(offset) ) {
            // TODO: test this
            vga_scroll(1);
        }
    }
    vga_set_cursor_offset(offset);
}
void vga_print_at(const char * str, int col, int row) {
    vga_set_cursor_offset(get_offset(col, row));
    vga_print_str(str);
}

