[bits 16]
switch_to_pm:
    cli                         ; 1. disable interrupts
    lgdt [gdt_descriptor]       ; 2. load GDT descriptor
    mov  eax, cr0
    or   eax, 0x1               ; 3. enable protected mode
    mov  cr0, eax
    JMP  CODE_SEG:init_pm       ; 4. far jump, force to switch to pm

[bits 32]
init_pm:
    mov  ax, DATA_SEG            ; 5. update segment registers
    mov  ds, ax
    mov  ss, ax
    mov  es, ax
    mov  fs, ax
    mov  gs, ax

; NOTE: foot stack base isn't the same as in grub, I'm sure it's not going to
; be a problem in the future (O_o).
    mov  esp, STACK_BASE_RM      ; 6. setup stack
    xor  ebp, ebp

    CALL BEGIN_PM               ; 7. move begin

