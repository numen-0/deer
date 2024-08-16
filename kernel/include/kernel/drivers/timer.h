#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

extern void init_timer(uint32_t freq);
uint16_t get_pit_value();

// NOTE: temporal location of this func
void sleep(uint32_t millis);

#endif // _TIMER_H
