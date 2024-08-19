#ifndef _ASM_TOOLS_H
#define _ASM_TOOLS_H

#define asm_halt() __asm__ __volatile__("hlt")
#define asm_sti()  __asm__ __volatile__("sti")
#define asm_cli()  __asm__ __volatile__("cli")

#endif // _ASM_TOOLS_H
