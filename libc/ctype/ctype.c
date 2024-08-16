
#include <ctype.h>

static const unsigned short _ctypes[256];
// const static unsigned short *ctypes = _ctypes + 1; // to take into account EOF (=-1), not needed for now

#define CLASSES()  \
    X(upper)      \
    X(lower)      \
    X(alpha)      \
    X(digit)      \
    X(xdigit)     \
    X(space)      \
    X(print)      \
    X(graph)      \
    X(blank)      \
    X(cntrl)      \
    X(punct)      \
    X(alnum)      \

#define BIT(n) 1 << n

#define  X(class) __##class,
enum {
    CLASSES()
};
#undef  X
#define X(class) IS_##class = BIT(__##class),
enum {
    CLASSES()
};
#undef  X
#define X(class) extern int is##class(int c) { return _ctypes[c] & IS_##class; }
CLASSES()
#undef  X

extern int tolower(int c);
extern int toupper(int c);
#define toupper(c) (islower(c) ? c + ('a' - 'A') : c)
#define tolower(c) (isupper(c) ? c + ('A' - 'a') : c)

static const unsigned short _ctypes[] = {
/* '^@': Null character */
    [0]   = IS_cntrl,
/* '^A': Start of Heading */
    [1]   = IS_cntrl,
/* '^B': Start of Text */
    [2]   = IS_cntrl,
/* '^C': End of Text */
    [3]   = IS_cntrl,
/* '^D': End of Transmission */
    [4]   = IS_cntrl,
/* '^E': Enquiry */
    [5]   = IS_cntrl,
/* '^F': Acknowledge */
    [6]   = IS_cntrl,
/* '^G': Bell, Alert */
    [7]   = IS_cntrl,
/* '^H': Backspace */
    [8]   = IS_cntrl,
/* '\t': Horizontal Tab */
    [9]   = IS_cntrl | IS_print | IS_space | IS_blank,
/* '\n': Line Feed */
    [10]  = IS_cntrl | IS_print | IS_space,
/* '^K': Vertical Tabulation */
    [11]  = IS_cntrl | IS_print | IS_space,
/* '^L': Form Feed */
    [12]  = IS_cntrl | IS_print | IS_space,
/* '^M': Carriage Return */
    [13]  = IS_cntrl | IS_print | IS_space,
/* '^N': Shift Out */
    [14]  = IS_cntrl,
/* '^O': Shift In */
    [15]  = IS_cntrl,
/* '^P': Data Link Escape */
    [16]  = IS_cntrl,
/* '^Q': Device Control One (XON) */
    [17]  = IS_cntrl,
/* '^R': Device Control Two */
    [18]  = IS_cntrl,
/* '^S': Device Control Three (XOFF) */
    [19]  = IS_cntrl,
/* '^T': Device Control Four */
    [20]  = IS_cntrl,
/* '^U': Negative Acknowledge */
    [21]  = IS_cntrl,
/* '^V': Synchronous Idle */
    [22]  = IS_cntrl,
/* '^W': End of Transmission Block */
    [23]  = IS_cntrl,
/* '^X': Cancel */
    [24]  = IS_cntrl,
/* '^Y': End of medium */
    [25]  = IS_cntrl,
/* '^Z': Substitute */
    [26]  = IS_cntrl,
/* '^[': Escape */
    [27]  = IS_cntrl,
/* '^\': File Separator */
    [28]  = IS_cntrl,
/* '^]': Group Separator */
    [29]  = IS_cntrl,
/* '^^': Record Separator */
    [30]  = IS_cntrl,
/* '^_': Unit Separator */
    [31]  = IS_cntrl,
/* ' ': Space */
    [32]  = IS_print | IS_print | IS_space | IS_blank,
/* '!': Exclamation mark */
    [33]  = IS_print | IS_graph | IS_punct,
/* '"': Double quotes (or speech marks) */
    [34]  = IS_print | IS_graph | IS_punct,
/* '#': Number sign */
    [35]  = IS_print | IS_graph | IS_punct,
/* '$': Dollar */
    [36]  = IS_print | IS_graph | IS_punct,
/* '%': Per cent sign */
    [37]  = IS_print | IS_graph | IS_punct,
/* '&': Ampersand */
    [38]  = IS_print | IS_graph | IS_punct,
/* ''': Single quote */
    [39]  = IS_print | IS_graph | IS_punct,
/* '(': Open parenthesis (or open bracket) */
    [40]  = IS_print | IS_graph | IS_punct,
/* ')': Close parenthesis (or close bracket) */
    [41]  = IS_print | IS_graph | IS_punct,
/* '*': Asterisk */
    [42]  = IS_print | IS_graph | IS_punct,
/* '+': Plus */
    [43]  = IS_print | IS_graph | IS_punct,
/* ',': Comma */
    [44]  = IS_print | IS_graph | IS_punct,
/* '-': Hyphen-minus */
    [45]  = IS_print | IS_graph | IS_punct,
/* '.': eriod;	Period, dot or full stop */
    [46]  = IS_print | IS_graph | IS_punct,
/* '/': Slash or divide */
    [47]  = IS_print | IS_graph | IS_punct,
/* '0': Zero */
    [48]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '1': One */
    [49]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '2': Two */
    [50]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '3': Three */
    [51]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '4': Four */
    [52]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '5': Five */
    [53]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '6': Six */
    [54]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '7': Seven */
    [55]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '8': Eight */
    [56]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* '9': Nine */
    [57]  = IS_print | IS_graph | IS_alnum | IS_digit | IS_xdigit,
/* ':': Colon */
    [58]  = IS_print | IS_graph | IS_punct,
/* ';': Semicolon */
    [59]  = IS_print | IS_graph | IS_punct,
/* '<': Less than (or open angled bracket) */
    [60]  = IS_print | IS_graph | IS_punct,
/* '=': Equals */
    [61]  = IS_print | IS_graph | IS_punct,
/* '>': Greater than (or close angled bracket) */
    [62]  = IS_print | IS_graph | IS_punct,
/* '?': Question mark */
    [63]  = IS_print | IS_graph | IS_punct,
/* '@': At sign */
    [64]  = IS_print | IS_graph | IS_punct,
/* 'A': Uppercase A */
    [65]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'B': Uppercase B */
    [66]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'C': Uppercase C */
    [67]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'D': Uppercase D */
    [68]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'E': Uppercase E */
    [69]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'F': Uppercase F */
    [70]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper | IS_xdigit,
/* 'G': Uppercase G */
    [71]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'H': Uppercase H */
    [72]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'I': Uppercase I */
    [73]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'J': Uppercase J */
    [74]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'K': Uppercase K */
    [75]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'L': Uppercase L */
    [76]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'M': Uppercase M */
    [77]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'N': Uppercase N */
    [78]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'O': Uppercase O */
    [79]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'P': Uppercase P */
    [80]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'Q': Uppercase Q */
    [81]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'R': Uppercase R */
    [82]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'S': Uppercase S */
    [83]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'T': Uppercase T */
    [84]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'U': Uppercase U */
    [85]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'V': Uppercase V */
    [86]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'W': Uppercase W */
    [87]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'X': Uppercase X */
    [88]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'Y': Uppercase Y */
    [89]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* 'Z': Uppercase Z */
    [90]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_upper,
/* '[': Opening bracket */
    [91]  = IS_print | IS_graph | IS_punct,
/* '\\': Backslash */
    [92]  = IS_print | IS_graph | IS_punct,
/* ']': Closing bracket */
    [93]  = IS_print | IS_graph | IS_punct,
/* '^': Caret - circumflex */
    [94]  = IS_print | IS_graph | IS_punct,
/* '_': Underscore */
    [95]  = IS_print | IS_graph | IS_punct,
/* '`': Grave accent */
    [96]  = IS_print | IS_graph | IS_punct,
/* 'a': Lowercase a */
    [97]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'b': Lowercase b */
    [98]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'c': Lowercase c */
    [99]  = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'd': Lowercase d */
    [100] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'e': Lowercase e */
    [101] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'f': Lowercase f */
    [102] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower | IS_xdigit,
/* 'g': Lowercase g */
    [103] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'h': Lowercase h */
    [104] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'i': Lowercase i */
    [105] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'j': Lowercase j */
    [106] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'k': Lowercase k */
    [107] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'l': Lowercase l */
    [108] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'm': Lowercase m */
    [109] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'n': Lowercase n */
    [110] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'o': Lowercase o */
    [111] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'p': Lowercase p */
    [112] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'q': Lowercase q */
    [113] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'r': Lowercase r */
    [114] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 's': Lowercase s */
    [115] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 't': Lowercase t */
    [116] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'u': Lowercase u */
    [117] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'v': Lowercase v */
    [118] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'w': Lowercase w */
    [119] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'x': Lowercase x */
    [120] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'y': Lowercase y */
    [121] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* 'z': Lowercase z */
    [122] = IS_print | IS_graph | IS_alnum | IS_alpha | IS_lower,
/* '{': Opening brace */
    [123] = IS_print | IS_graph | IS_punct,
/* '|': Vertical bar */
    [124] = IS_print | IS_graph | IS_punct,
/* '}': Closing brace */
    [125] = IS_print | IS_graph | IS_punct,
/* '~': Equivalency sign - tilde */
    [126] = IS_print | IS_graph | IS_punct,
/* '': Delete */
    [127] = IS_cntrl,
/* everything else will be unset to 0 */
};


// another implementation of the rules 
/*
#define isdigit(c) ('0' <= c && c <= '9')
#define isxdigit(c) \
    (isdigit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))

#define isblank(c) (c == ' ' || c == '\t')
#define isspace(c) (c == ' ' || (9 <= c && c <= 13))
#define islower(c) ('a' <= c && c <= 'z')
#define isupper(c) ('A' <= c && c <= 'Z')

#define ispunct(c) \
    ((33 <= c && c <= 47) || (58 <= c && c <= 64) || \
     (91 <= c && c <= 96) || (123 <= c && c <= 126))
#define isalpha(c) (islower(c) || isupper(c))
#define isalnum(c) (isalpha(c) || isdigit(c))

#define iscntrl(c) ((0 <= c && c <= 31) || c == 127)
#define isgraph(c) (33 <= c && c <= 126)
#define isprint(c) (isgraph(c) || isspace(c))
*/
