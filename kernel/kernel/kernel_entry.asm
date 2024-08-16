[bits 32]
[extern kernel_main]
global _kernel_start ; Make sure this is the entry symbol

_kernel_start:
    CALL kernel_main
    RET
