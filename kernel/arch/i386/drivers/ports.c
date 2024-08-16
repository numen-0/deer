
#include <stdint.h>
#include <kernel/ports.h>

extern inline uint8_t port_byte_in(uint16_t port) {
    // "=a" (result) -> put AL register in variable RESULT when finished
    // "d"  (port)   -> load DX with port
    uint8_t result;
    asm ("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}
extern inline void port_byte_out(uint16_t port, uint8_t data) {
    // "a" (data) -> load AL with data
    // "d" (port) -> load DX with port
    asm volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}
extern inline uint16_t port_word_in(uint16_t port) {
    uint16_t result;
    asm ("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}
extern inline void port_word_out(uint16_t port, uint16_t data) {
    asm volatile ("outw %0, %1" : : "a" (data), "dN" (port));
}
