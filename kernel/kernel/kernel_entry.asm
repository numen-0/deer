[bits 32]
[extern kernel_main]
global _kernel_main  ; Make sure this is the entry symbol

_kernel_main:
    call kernel_main
    jmp $
