#ifndef _KEYBOARD_LAYOUT_H

#ifndef K_LAYOUT // default ES
#define SC_LSHFT    0x2a
#define SC_RSHFT    0x36
#define SC_LCTRL    0x1d
#define SC_ALT      0x38
#define SC_SUPER    0x38
#define SC_ALTGR    0x5b
#define SC_BLCKM    0x3a
#define SC_EXTD2    0xe0

//  X(SC,   NORM,    SHIFT,   ALTG,    EXTD2)
#define LAYOUT() \
    X(0x00, K_UNKW,  K_UNKW,  K_UNKW,  K_UNKW) \
/* mod keys */\
    X(0x1d, K_LCTRL, K_LCTRL, K_LCTRL, K_UNKW) \
    X(0x2a, K_LSHFT, K_LSHFT, K_LSHFT, K_UNKW) \
    X(0x36, K_RSHFT, K_RSHFT, K_RSHFT, K_UNKW) \
    X(0x38, K_ALT,   K_ALT,   K_ALT,   K_SUPER)\
    X(0x3a, K_BLCKM, K_BLCKM, K_BLCKM, K_UNKW) \
    X(0x5b, K_UNKW,  K_UNKW,  K_UNKW,  K_ALTGR)\
/* F1-12 */\
    X(0x3b, K_F01,   K_F01,   K_F01,   K_UNKW) \
    X(0x3c, K_F02,   K_F02,   K_F02,   K_UNKW) \
    X(0x3d, K_F03,   K_F03,   K_F03,   K_UNKW) \
    X(0x3e, K_F04,   K_F04,   K_F04,   K_UNKW) \
    X(0x3f, K_F05,   K_F05,   K_F05,   K_UNKW) \
    X(0x40, K_F06,   K_F06,   K_F06,   K_UNKW) \
    X(0x41, K_F07,   K_F07,   K_F07,   K_UNKW) \
    X(0x42, K_F08,   K_F08,   K_F08,   K_UNKW) \
    X(0x43, K_F09,   K_F09,   K_F09,   K_UNKW) \
    X(0x44, K_F10,   K_F10,   K_F10,   K_UNKW) \
    X(0x57, K_F11,   K_F11,   K_F11,   K_UNKW) \
    X(0x58, K_F12,   K_F12,   K_F12,   K_UNKW) \
/* special keys */\
    X(0x01, K_ESC,   K_ESC,   K_ESC,   K_UNKW) \
    X(0x0e, K_BKSPC, K_UNKW,  K_UNKW,  K_UNKW) \
    X(0x0f, K_TAB,   K_UNKW,  K_UNKW,  K_UNKW) \
    X(0x1c, K_ENTER, K_UNKW,  K_UNKW,  K_UNKW) \
    X(0x39, K_SPCBR, K_UNKW,  K_UNKW,  K_UNKW) \
    X(0x48, K_UNKW,  K_UNKW,  K_UNKW,  K_UP  ) \
    X(0x4b, K_UNKW,  K_UNKW,  K_UNKW,  K_LEFT) \
    X(0x4d, K_UNKW,  K_UNKW,  K_UNKW,  K_RIGHT)\
    X(0x50, K_UNKW,  K_UNKW,  K_UNKW,  K_DOWN) \
/* nums keys */\
    X(0x02, K_ONE,   K_EMARK, K_VBAR,  K_UNKW) \
    X(0x03, K_TWO,   K_DQUOT, K_AT,    K_UNKW) \
    X(0x04, K_THREE, K_UNKW,  K_HASH,  K_UNKW) \
    X(0x05, K_FOUR,  K_DOLLR, K_UNKW,  K_UNKW) \
    X(0x06, K_FIVE,  K_PRCNT, K_UNKW,  K_UNKW) \
    X(0x07, K_SIX,   K_AMP,   K_UNKW,  K_UNKW) \
    X(0x08, K_SEVEN, K_SLASH, K_UNKW,  K_UNKW) \
    X(0x09, K_EIGHT, K_OPARN, K_UNKW,  K_UNKW) \
    X(0x0a, K_NINE,  K_CPARN, K_UNKW,  K_UNKW) \
    X(0x0b, K_ZERO,  K_EQ,    K_UNKW,  K_UNKW) \
/* alpha keys */\
    X(0x10, K_q,     K_Q,     K_UNKW,  K_UNKW) \
    X(0x11, K_w,     K_W,     K_UNKW,  K_UNKW) \
    X(0x12, K_e,     K_E,     K_UNKW,  K_UNKW) \
    X(0x13, K_r,     K_R,     K_UNKW,  K_UNKW) \
    X(0x14, K_t,     K_T,     K_UNKW,  K_UNKW) \
    X(0x15, K_y,     K_Y,     K_UNKW,  K_UNKW) \
    X(0x16, K_u,     K_U,     K_UNKW,  K_UNKW) \
    X(0x17, K_i,     K_I,     K_UNKW,  K_UNKW) \
    X(0x18, K_o,     K_O,     K_UNKW,  K_UNKW) \
    X(0x19, K_p,     K_P,     K_UNKW,  K_UNKW) \
    X(0x1e, K_a,     K_A,     K_UNKW,  K_UNKW) \
    X(0x1f, K_s,     K_S,     K_UNKW,  K_UNKW) \
    X(0x20, K_d,     K_D,     K_UNKW,  K_UNKW) \
    X(0x21, K_f,     K_F,     K_UNKW,  K_UNKW) \
    X(0x22, K_g,     K_G,     K_UNKW,  K_UNKW) \
    X(0x23, K_h,     K_H,     K_UNKW,  K_UNKW) \
    X(0x24, K_j,     K_J,     K_UNKW,  K_UNKW) \
    X(0x25, K_k,     K_K,     K_UNKW,  K_UNKW) \
    X(0x26, K_l,     K_L,     K_UNKW,  K_UNKW) \
    X(0x2c, K_z,     K_Z,     K_UNKW,  K_UNKW) \
    X(0x2d, K_x,     K_X,     K_UNKW,  K_UNKW) \
    X(0x2e, K_c,     K_C,     K_UNKW,  K_UNKW) \
    X(0x2f, K_v,     K_V,     K_UNKW,  K_UNKW) \
    X(0x30, K_b,     K_B,     K_UNKW,  K_UNKW) \
    X(0x31, K_n,     K_N,     K_UNKW,  K_UNKW) \
    X(0x32, K_m,     K_M,     K_UNKW,  K_UNKW) \
/* simbols keys */\
    X(0x0c, K_SQUOT, K_QMARK, K_UNKW,  K_UNKW) \
    X(0x0d, K_UNKW,  K_UNKW,  K_UNKW,  K_UNKW) \
    X(0x1a, K_GACNT, K_CARET, K_OBRAQ, K_UNKW) \
    X(0x1b, K_PLUS,  K_ASTER, K_CBRAQ, K_UNKW) \
    X(0x27, K_TILDE, K_UNKW,  K_TILDE, K_UNKW) \
    X(0x28, K_OBRCE, K_UNKW,  K_OBRCE, K_UNKW) \
    X(0x29, K_BLASH, K_UNKW,  K_BLASH, K_UNKW) \
    X(0x2b, K_CBRCE, K_UNKW,  K_CBRCE, K_UNKW) \
    X(0x33, K_COMMA, K_SCLON, K_UNKW,  K_UNKW) \
    X(0x34, K_DOT,   K_COLON, K_UNKW,  K_UNKW) \
    X(0x35, K_MINUS, K_LBAR,  K_UNKW,  K_UNKW) \
    X(0x56, K_LTHAN, K_GTHAN, K_UNKW,  K_UNKW) \
// #elif   KEYBOARD_LAYOUT == us
// ...
#endif // KEYBOARD_LAYOUT

#endif // _KEYBOARD_LAYOUT_H
