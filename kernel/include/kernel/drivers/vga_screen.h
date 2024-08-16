#ifndef __VGA_SCREEN_H__
#define __VGA_SCREEN_H__

typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_YELLOW,
    VGA_COLOR_WHITE,
    VGA_COLOR_LIGHT_BLACK,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_YELLOW,
    VGA_COLOR_LIGHT_WHITE,
} vga_16_color;

// text mode
extern void vga_change_color(vga_16_color fg, vga_16_color bg);
extern void vga_change_color_bg(vga_16_color bg);
extern void vga_change_color_fg(vga_16_color fg);

extern void vga_clear_screen(void);
extern void vga_print_at(const char * str, int col, int row);
extern void vga_print_str(const char * str);
extern void vga_putc(char c);
extern void vga_scroll(int lines);

#endif // __VGA_SCREEN_H__
