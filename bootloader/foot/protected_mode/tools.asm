[bits 32]

%define VIDEO_MEMORY    0xb8000
%define WHITE_ON_BLACK  0x0f

print_pm:       ; prints a null - te rminated string pointed to by EDX
    pusha
    mov  edx, VIDEO_MEMORY  ; Set edx to the start of vid mem.
print_string_pm_loop:
    mov  al, [ebx]          ; Store the char at EBX in AL

    mov  ah, WHITE_ON_BLACK ; Store the att ributes in AH
    cmp  al, 0
    JE   done               ; if ( al == 0 ), at end of string
    mov  [edx], ax
    add  ebx, 1
    add  edx, 2

    JMP print_string_pm_loop ; loop around to print the next char.
done:
    popa
    RET
