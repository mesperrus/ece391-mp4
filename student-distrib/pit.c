/* pit.c - Init for PIT */

#include "pit.h"
#include "x86_desc.h"
#include "i8259.h"

#define INT_INTERVAL                 15 // timer interrupt interval in ms
#define PIT_IRQ                     0x00


void pit_init() {
    uint16_t divisor = 1193182 * INT_INTERVAL / 1000;

    cli();
    outb(0x36, 0x43);
    outb((uint8_t) (divisor & 0xFF), 0x40);
    outb((uint8_t) ((divisor >> 8) & 0xFF), 0x40);

    enable_irq(PIT_IRQ);
}
