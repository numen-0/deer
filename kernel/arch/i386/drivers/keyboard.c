/*
 * NOTE: for now theres not any security for interrupts while we are handling 
 *       keyboard_callback(). Maybe a future addition could be to add a key 
 *       queue and handle them in order, and cool stuff like that.
 */
#include <stdint.h>

#include <kernel/isr.h>
#include <kernel/ports.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/vga_screen.h>
#include <kernel/io.h>

#include "./keyboard_layout.h"


static key_flags kflags = 0;

// [tables]
// k_to_ascii
static const char k_to_ascii[128] = {
    [K_UNKW]  = '\0',
/* mod keys */
    [K_ESC]   = '\0', [K_ALTGR] = '\0', [K_ALT]   = '\0', [K_BLCKM] = '\0',
    [K_LCTRL] = '\0', [K_LSHFT] = '\0', [K_RSHFT] = '\0', [K_SUPER] = '\0',
/* F1-12 */
    [K_F01] = '\0', [K_F02] = '\0', [K_F03] = '\0', [K_F04] = '\0',
    [K_F05] = '\0', [K_F06] = '\0', [K_F07] = '\0', [K_F08] = '\0',
    [K_F09] = '\0', [K_F10] = '\0', [K_F11] = '\0', [K_F12] = '\0',
/* special keys */
    [K_ENTER] = '\n',[K_SPCBR] = ' ',  [K_TAB]   = '\t',[K_BKSPC] = '\b',
    [K_LEFT]  = '\0',[K_UP]    = '\0', [K_RIGHT] = '\0',[K_DOWN]  = '\0',
/* nums */
    [K_ONE]  = '1',  [K_TWO]   = '2', [K_THREE] = '3', [K_FOUR]  = '4',
    [K_FIVE] = '5',  [K_SIX]   = '6', [K_SEVEN] = '7', [K_EIGHT] = '8',
    [K_NINE] = '9',  [K_ZERO]  = '0',
/* alphabet */
    [K_q] = 'q', [K_w] = 'w', [K_e] = 'e', [K_r] = 'r', [K_t] = 't',
    [K_y] = 'y', [K_u] = 'u', [K_i] = 'i', [K_o] = 'o', [K_p] = 'p',
    [K_a] = 'a', [K_s] = 's', [K_d] = 'd', [K_f] = 'f', [K_g] = 'g',
    [K_h] = 'h', [K_j] = 'j', [K_k] = 'k', [K_l] = 'l', [K_z] = 'z',
    [K_x] = 'x', [K_c] = 'c', [K_v] = 'v', [K_b] = 'b', [K_n] = 'n',
    [K_m] = 'm',
    [K_Q] = 'Q', [K_W] = 'W', [K_E] = 'E', [K_R] = 'R', [K_T] = 'T',
    [K_Y] = 'Y', [K_U] = 'U', [K_I] = 'I', [K_O] = 'O', [K_P] = 'P',
    [K_A] = 'A', [K_S] = 'S', [K_D] = 'D', [K_F] = 'F', [K_G] = 'G',
    [K_H] = 'H', [K_J] = 'J', [K_K] = 'K', [K_L] = 'L', [K_Z] = 'Z',
    [K_X] = 'X', [K_C] = 'C', [K_V] = 'V', [K_B] = 'B', [K_N] = 'N',
    [K_M] = 'M',
/* simbols */
    [K_EQ]    = '=', [K_PLUS]  = '+', [K_MINUS] = '-', [K_ASTER] = '*',
    [K_LTHAN] = '<', [K_GTHAN] = '>', [K_AMP]   = '*',
    [K_GACNT] = '`', [K_TILDE] = '~',
    [K_OBRCE] = '[', [K_CBRCE] = ']', [K_OPARN] = '(', [K_CPARN] = ')',
    [K_OBRAQ] = '{', [K_CBRAQ] = '}', [K_DQUOT] = '"', [K_SQUOT] = '\'',
    [K_HASH]  = '#', [K_DOLLR] = '$', [K_AT]    = '@', [K_PRCNT] = '%',
    [K_COMMA] = ',', [K_DOT]   = '.', [K_COLON] = ':', [K_SCLON] = ';',
    [K_QMARK] = '?', [K_EMARK] = '!',
    [K_SLASH] = '/', [K_BLASH] = '\\', [K_VBAR]  = '|', [K_LBAR]  = '_',
    [K_CARET] = '^',
};

#define OFF_NORM  (0)
#define OFF_SHIFT (1 << 8)
#define OFF_ALTG  (2 << 8)
#define OFF_EXTD2 (4 << 8)
//      X(SC, NORM,   SHIFT,   ALTG,   EXTD2)
#define X(sc, k_norm, k_shift, k_altg, k_extd2) \
    [OFF_NORM  + sc] = k_norm,                  \
    [OFF_SHIFT + sc] = k_shift,                 \
    [OFF_ALTG  + sc] = k_altg,                  \
    [OFF_EXTD2 + sc] = k_extd2,
static const uint8_t sc_to_k[OFF_EXTD2 << 1] = { LAYOUT() };
#undef X

static void keyboard_callback(registers_t *regs) {
    (void)regs; // unused
    /* the PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    // check if key uses extend
    if ( scancode == SC_EXTD2  ) { kflags |= K_FLAG_EXTD2; return; }
    // kflags
    switch ( scancode ) {
        case SC_LSHFT: { kflags |= K_FLAG_SHIFT; return; }
        case SC_RSHFT: { kflags |= K_FLAG_SHIFT; return; }
        case SC_LCTRL: { kflags |= K_FLAG_CTRL;  return; }
        case SC_ALT:   {
            if (kflags & K_FLAG_EXTD2) {
                kflags |= K_FLAG_ALTGR;
                kflags &= ~K_FLAG_EXTD2;
            } else {
                kflags |= K_FLAG_ALT;
            } return;
        } case SC_BLCKM: { kflags |= K_FLAG_BLCKM; return; }
        case SC_LSHFT + 0x80: { kflags &= ~K_FLAG_SHIFT; return; }
        case SC_RSHFT + 0x80: { kflags &= ~K_FLAG_SHIFT; return; }
        case SC_LCTRL + 0x80: { kflags &= ~K_FLAG_CTRL;  return; }
        case SC_ALT   + 0x80: {
            if (kflags & K_FLAG_EXTD2) {
                kflags &= ~K_FLAG_ALTGR & ~K_FLAG_EXTD2;
            } else {
                kflags &= ~K_FLAG_ALT;
            } return;
        } case SC_BLCKM + 0x80: { kflags &= ~K_FLAG_BLCKM; return; }
    }
    // release sc
    if ( scancode > 0x7F ) { kflags |= K_FLAG_KEYUP; }
    else { kflags &= ~K_FLAG_KEYUP; }

    key_info key = { .kf = kflags };
    if ( kflags == 0 ) {
        key.kc = sc_to_k[OFF_NORM + (int)scancode];
    } else if ( kflags & K_FLAG_EXTD2 ) {
        key.kc = sc_to_k[OFF_EXTD2 + (int)scancode];
        kflags &= ~K_FLAG_EXTD2;
    } else if ( kflags & K_FLAG_ALTGR ) {
        key.kc = sc_to_k[OFF_ALTG + (int)scancode];
    } else if ( kflags & K_FLAG_BLCKM ) {
        if ( kflags & K_FLAG_SHIFT ) {
            key.kc = sc_to_k[OFF_NORM + (int)scancode];
        } else {
            key.kc = sc_to_k[OFF_SHIFT + (int)scancode];
        }
    } else if ( kflags & K_FLAG_SHIFT ) {
        key.kc = sc_to_k[OFF_SHIFT + (int)scancode];
    } else {
        key.kc = sc_to_k[OFF_NORM + (int)scancode];
    }
    key.rep = k_to_ascii[key.kc];

    in_keyboard(key);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}

