#include <kernel/drivers/vga_screen.h>
#include <kernel/drivers/timer.h>
#include <kernel/isr.h>
#include <kernel/ports.h>

// NOTE: atomic stuff here in a future
static volatile uint64_t tick = 0;
static volatile uint32_t frequency = 1;

static void timer_callback(registers_t *regs) {
    (void)regs; // unused
    // NOTE: atomic write
    tick++;
}

/* NOTE: if freq doens divide the hardware clock "nicely" the intervals aren't 
 *       going to be "exact". 
 *       formula: 
 *          count = 1.193182 MHz / freq (Hz);
 *       e.g.:
 *          T = 10ms -> f = 1/(0.1s) = 100 Hz;
 *          count = 1193182 / (100) = 11931.82 ~ 11931; (.82 is lost)
 */
void init_timer(uint32_t freq) {
    frequency = freq;

    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193182 Hz */
    uint32_t count = 1193182 / freq;
    uint8_t  low  = (uint8_t)(count & 0xFF);
    uint8_t  high = (uint8_t)((count >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

uint16_t get_pit_value() {
    port_byte_out(0x43, 0x00); // Latch the count
    uint8_t low = port_byte_in(0x40);
    uint8_t high = port_byte_in(0x40);
    return (high << 8) | low;
}
// *at least* wait millis
void sleep(uint32_t millis) {
    /* formula: targer = freq * millis / 1000 (millis) */
    uint64_t target = tick + ((uint64_t)millis * frequency) / 1000;
    while ( target != tick ) {
        __asm__ __volatile__ ("hlt");
    };
}
