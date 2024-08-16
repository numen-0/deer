[bits 16]

print_string_rm: ; in si: str
    pusha
    mov  ah, 0x0e   ; INT 10 + ah = 0x0e -> scrolling teletype BIOS
.print_string_next_char:
    mov  al, [si]
    test al, al
    JE   .print_string_out
    INT  0x10       ; print to screen
    inc  si
    JMP  .print_string_next_char
.print_string_out:
    popa
    RET
print_newline_rm:
    pusha
    mov  ah, 0x0e        ; BIOS teletype function
    mov  al, 0x0D        ; carriage return (CR)
    INT  0x10            ; print
    mov  al, 0x0A        ; line feed (LF)
    INT  0x10            ; print
    popa
    RET
print_hex_2B_rm: ; in ax: 16b
    pusha
    mov  cx, 4                  ; process each digit
    JMP  print_hex_rm
print_hex_1B_rm: ; in al: 8b
    pusha
    rol  ax, 8
    mov  byte [HEX_OUT+2+2], 0  ; 0x00_0
    mov  cx, 2                  ; process each digit
print_hex_rm:
    mov  di, HEX_OUT+2      ; point to 0x*000
    mov  si, HEX_MAP        ; load base address
.print_hex_next_digit:
    rol  ax, 4              ; extract value
    mov  bl, al             ;
    and  bx, 0x0f           ;
    mov  bl, [si+bx]        ;
    mov  [di], bl           ; store character
    inc  di                 ;
    LOOP .print_hex_next_digit
    mov  si, HEX_OUT
    CALL print_string_rm
    popa
    RET

;0 | boot: BIOS error
;1 | 0x??   ->   INT 0x?? call
;2 | 0x??   ->   AH value before INT
;some values: (https://en.wikipedia.org/wiki/BIOS_interrupt_call)
;   INT     AH        desk:
;   0x10    0x00    : video services: set video mode
;   0x10    0x0e    :                 write character in TTY mode
;   0x13    0x02    : disk services:  read sectors
BIOS_error: ; AH (AH call function), AL (int call); unpolite
    mov   si, BIOS_ERROR_MSG
    CALL  print_string_rm
    CALL  print_hex_1B_rm       ; int 0x?? call
    CALL  print_newline_rm
    mov   al, ah
    CALL  print_hex_1B_rm       ; AH call function (value of AH before int 0x??)
    CALL  print_newline_rm
    JMP   hang

HEX_OUT:                db "0x0000", 0
HEX_MAP:                db "0123456789abcdef"
BIOS_ERROR_MSG:         db "boot: BIOS error", 0x0D, 0x0A, 0

