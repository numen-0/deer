; NOTE: the bootloader needs to be 512 (the first 510 because the magic num at
;       the end need 2B) bytes or less to fit in the segment, if we surpass that
;       limit we need to start creating modules and load them...
;
;       keep it simple

%define STACK_BASE_PM           0x8000
%define STACK_BASE_RM           0x9_0000
%define BOOT_SEG                0x07c0
%define INIT_SEG                0x1000
%define MAX_LOADABLE_BYTES      (0xFFFF - INIT_SEG + 1)
%define SECTOR_SIZE             512
%define MAX_LOADABLE_SECTORS    (MAX_LOADABLE_BYTES / SECTOR_SIZE)

[bits 16]
[org 0x7c00]    ; Tell the assembler where this code will be loaded
global _start

_start:         ; BOOT: start
    mov  [BOOT_DRIVE], dl   ; BIOS stores our boot drive in DL
;clear screen:
    mov ah, 0x00            ; BIOS function 0x00: set video mode
    mov al, 0x03            ; video mode 0x03: 80x25 text mode, 16 colors
    int 0x10                ; BIOS interrupt 0x10
;set_stack:
    mov  bp, STACK_BASE_PM  ; set stack base
    mov  sp, bp
;load_kernel:
    cld                     ; clear direction flag
    mov  bx, INIT_SEG       ; load n sectors to 0x0000:INIT_SEG (ES:BX)
    mov  dh, 15             ; from the boot disk (each sector 512B)
    mov  dl, [BOOT_DRIVE]   ; select our drive
    CALL disk_load
;start_kerner_in_pm:
    CALL switch_to_pm
hang:
	cli
.hang:	hlt
    JMP $

%include "foot/real_mode/disk.asm"
%include "foot/real_mode/gdt.asm"
%include "foot/real_mode/switch_to_pm.asm"
%include "foot/real_mode/tools.asm"

[bits 32]

;%include "protected_mode/tools.asm"

BEGIN_PM:
    call INIT_SEG   ; give control to the kernel
    JMP $           ; loop in case kernel returns

BOOT_DRIVE db 0

; padding
times 510 - ($-$$) db 0

; magic number
dw 0xaa55

