#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stdint.h>

extern void init_keyboard(void);

enum {
    K_UNKW,
/* mod keys */
    K_ESC,   K_ALT,   K_ALTGR, K_BLCKM,
    K_LCTRL, K_LSHFT, K_RSHFT, K_SUPER,
/* F1-12 */
    K_F01, K_F02, K_F03, K_F04, K_F05, K_F06,
    K_F07, K_F08, K_F09, K_F10, K_F11, K_F12,
/* special keys */
    K_ENTER, K_SPCBR, K_TAB,   K_BKSPC,
    K_LEFT,  K_UP,    K_RIGHT, K_DOWN,
/* nums */
    K_ONE,   K_TWO,   K_THREE, K_FOUR, K_FIVE,
    K_SIX,   K_SEVEN, K_EIGHT, K_NINE, K_ZERO,
/* alphabet */
    K_A, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M,
    K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z,
    K_a, K_b, K_c, K_d, K_e, K_f, K_g, K_h, K_i, K_j, K_k, K_l, K_m,
    K_n, K_o, K_p, K_q, K_r, K_s, K_t, K_u, K_v, K_w, K_x, K_y, K_z,
/* simbols */
    K_EQ,    K_PLUS,  K_MINUS, K_ASTER, K_LTHAN, K_GTHAN, K_AMP,
    K_GACNT, K_TILDE,
    K_OBRCE, K_CBRCE, K_OPARN, K_CPARN, K_OBRAQ, K_CBRAQ, K_DQUOT, K_SQUOT, 
    K_HASH,  K_DOLLR, K_AT,    K_PRCNT,
    K_COMMA, K_DOT,   K_COLON, K_SCLON, K_QMARK, K_EMARK,
    K_SLASH, K_BLASH, K_VBAR,  K_LBAR,  K_CARET,
};

enum {
    K_FLAG_KEYUP = 1 << 0,
    K_FLAG_SHIFT = 1 << 1,
    K_FLAG_CTRL  = 1 << 2,
    K_FLAG_ALT   = 1 << 3,
    K_FLAG_ALTGR = 1 << 4,
    K_FLAG_BLCKM = 1 << 5,
    K_FLAG_EXTD2 = 1 << 6,
};

typedef uint8_t key_code;
typedef uint8_t key_flags;

typedef struct {
    key_code  kc;
    key_flags kf;
    char      rep; 
    char      _;    /* padding */
} __attribute__((packed)) key_info;

#endif // _KEYBOARD_H
