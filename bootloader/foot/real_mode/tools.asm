[bits 16]

print_char: ; in al, unpolite [ax]
    mov  ah, 0x0e        ; BIOS teletype function
    INT  0x10            ; print
print_string_rm: ; in bx: str
    pusha
    mov  ah, 0x0e   ; INT 10 + ah = 0x0e -> scrolling teletype BIOS
.print_string_next_char:
    mov  al, [bx]
    test al, al
    JE   .print_string_out
    INT  0x10       ; print to screen
    inc  bx
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
print_hex_2B_rm: ; in dx: 16b
    pusha
    mov  cx, 4              ; process each digit
    JMP  print_hex_next_digit
print_hex_1B_rm: ; in dh: 8b
    pusha
    mov  byte [HEX_OUT+2+2], 0 ; 0x00_0
    mov  cx, 2              ; process each digit
    mov  bx, HEX_OUT+2
print_hex_next_digit:
    rol  dx, 4              ; extract value
    mov  al, dl             ;
    and  ax, 0x000f         ;
    mov  si, HEX_MAP        ; load base address
    add  si, ax             ; offset
    mov  al, [si]           ;
    mov  [bx], al           ; store character
    inc  bx                 ;
    LOOP print_hex_next_digit
    mov  bx, HEX_OUT
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
BIOS_error: ; CH (AH call function), DH (int call); unpolite
    mov   bx, BIOS_ERROR_MSG
    CALL  print_string_rm
    CALL  print_hex_1B_rm       ; int 0x?? call
    CALL  print_newline_rm
    mov   dh, ch
    CALL  print_hex_1B_rm       ; AH call function (value of AH before int 0x??)
    CALL  print_newline_rm
    JMP   hang

HEX_OUT:                db "0x0000", 0
HEX_MAP:                db "0123456789abcdef"
BIOS_ERROR_MSG:         db "boot: BIOS error", 0x0D, 0x0A, 0

; NOTE: to big to fit in a sector if we add this
; display info about memory drive
;drive_info:         ; in: dl = drive
;    pusha
;    push dx                 ; save dl
;    mov  ah, 0x08           ; BIOS get drive parameters
;    INT  0x13               ; BIOS interrupt
;    JC   .drive_info_error  ; jump if error ( i.e. carry flag set )
;    mov  bx, DRIVE_INFO_MSG ; print info
;    CALL print_string_rm
;    pop  ax         ; retrieve dl: drive num (overriten by INT (driver count))
;    push dx         ; save dh
;    mov  dx, ax
;    and  dx, 0x00ff     ; num
;    mov  bx, DRIVE_INFO_NUMB_MSG
;    CALL print_string_rm
;    CALL print_hex_2B_rm
;    cmp  dl, 0x80
;    mov  bx, DRIVE_INFO_TYPE1    ; save some bytes in a jmp
;    JNC  .drive_info_t_out       ; floppy < 0x80; hard >= 0x80
;    mov  bx, DRIVE_INFO_TYPE0
;.drive_info_t_out:
;    CALL print_string_rm
;    pop  dx             ; retrieve dh: logical last indx of heads (base 0)
;    shr  dx, 8
;    inc  dx             ; +1
;    mov  bx, DRIVE_INFO_HEAD_MSG
;    CALL print_string_rm
;    CALL print_hex_2B_rm
;    mov  dx, cx         ; sectors
;    and  dx, 0x003f     ; [5:0] logical last index of sectors per track (base 1)
;    mov  bx, DRIVE_INFO_SECT_MSG
;    CALL print_string_rm
;    CALL print_hex_2B_rm
;    mov  dx, cx         ; cylinder
;    shl  dx, 2          ; [7:6]_[15:8]  logical last index of cylinders (base 0)
;    mov  dl, ch
;    and  dx, 0x03ff
;    inc  dx             ; +1
;    mov  bx, DRIVE_INFO_CLDR_MSG
;    CALL print_string_rm
;    CALL print_hex_2B_rm
;    popa
;    RET
;.drive_info_error:
;    mov  ch, 0x08
;    mov  dh, 0x13
;    JMP  BIOS_error
;    JMP  $
;
;DRIVE_INFO_MSG:         db "info:", 0
;DRIVE_INFO_NUMB_MSG:    db 0x0D, 0x0A, "  n: ", 0
;    DRIVE_INFO_TYPE0:       db "[f]", 0             ; floppy drive
;    DRIVE_INFO_TYPE1:       db "[h]", 0             ; hard drive
;DRIVE_INFO_HEAD_MSG:    db 0x0D, 0x0A, "  h: ", 0
;DRIVE_INFO_SECT_MSG:    db 0x0D, 0x0A, "  s: ", 0
;DRIVE_INFO_CLDR_MSG:    db 0x0D, 0x0A, "  c: ", 0
