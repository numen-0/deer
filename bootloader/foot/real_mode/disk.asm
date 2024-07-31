[bits 16]

disk_load:      ; load DH sectors to ES:BX from drive DL; unpolite
    pusha
    push dx

    mov  ah, 0x02 ; read mode
    mov  al, dh   ; read dh number of sectors
    mov  cl, 0x02 ; start reading from second sector ( 1 = boot sector )
    mov  ch, 0x00 ; cylinder 0
    mov  dh, 0x00 ; head 0

    INT  0x13            ; BIOS interrupt
    JC   .disk_error    ; jump if error ( i.e. carry flag set )

    pop  dx             ; restore DX
    cmp  al, dh         ; if AL ( sectors read ) != DH ( sectors expected )
    JNE  .disk_sectors_error
    popa
    RET
.disk_error:
;    JMP  .disk_error_out
.disk_sectors_error:
;.disk_error_out:
    mov  ch, 0x02
    mov  dh, 0x13
    JMP  BIOS_error

; is this necesary?
; mov ax, 0x4100   ; Check if LBA is supported
; mov bx, 0x55AA   ; Signature
; int 0x13
; JC  not_supported  ; Jump if carry flag is set (not supported)
; test ah, 1        ; Check LBA support flag
; JZ  not_supported  ; Jump if zero (not supported)
; ; LBA supported

