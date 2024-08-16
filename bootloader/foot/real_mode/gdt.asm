[bits 16]

gdt_start:  ; Global Descriptor Table
gdt_null:   ; mandatory null descriptor
    dd 0x00     ; 4 bytes
    dd 0x00

gdt_code:   ; code segment descriptor
; base = 0x00; limit = 0xfffff;
; flags:
;   1st : [present:1] [privilege:00] [d escriptor type:1]           -> 1001b
;   type: [code:1] [expand down:0] [writable:1] [accessed:0]        -> 1010b
;   2nd : [granularity:1] [32bit default:1] [64-bit seg:0] [AVL:0]  -> 1100b
    dw 0xffff    ; limit (seg. lenght)  - (bits 0-15)
    dw 0x00      ; segment base         - (bits 0-15)
    db 0x00      ; segment base         - (bits 16-23)
    db 10011010b ; 1st + type flags     - (8 bits)
    db 11001111b ; 2nd flags + limit    - (4 bits) + (bits 16-19)
    db 0x00      ; segment base, bits 24-31

gdt_data:   ; data segment descriptor
; Same as code segment except for the type flags [code:0]:
; type flags: [code:0] [expand down:0] [writable:1] [accessed:0] -> 0010b
    dw 0xffff    ; limit (seg. lenght)  - (bits 0-15)
    dw 0x00      ; segment base         - (bits 0-15)
    db 0x00      ; segment base         - (bits 16-23)
    db 10010010b ; 1st + type flags     - (8 bits)
    db 11001111b ; 2nd flags + limit    - (4 bits) + (bits 16-19)
    db 0x00      ; segment base, bits 24-31
gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; gdt size-1           (16 bit)
    dd gdt_start                ; start address of gdt (32 bit)

; Define some handy constants for the GDT segment de scriptor offsets, which
; are what segment registers must contain when in protected mode. For example,
; when we set DS = 0x10 in PM, the CPU knows that we mean it to use the segment
; described at offset 0x10 (i.e. 16 bytes) in our GDT, which in our case is the
; DATA segment (0x00 -> NULL; 0x08 -> CODE; 0x10 -> DATA)
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
