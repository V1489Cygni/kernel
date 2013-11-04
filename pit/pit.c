#include "pit.h"

#include "../irq/irq.h"
#include "../output/output.h"
#include "../service/service.h"

int timer_ticks = 0;

void timer_phase(int hz) {
    int divisor = 1193180 / hz;    
    outportb(0x43, 0x36);             
    outportb(0x40, divisor & 0xFF);  
    outportb(0x40, divisor >> 8);   
}

void timer_handler(struct regs *r) {
    timer_ticks++;    
    if (timer_ticks % 18 == 0) {
        //print((unsigned char*)"One second has passed\n");
    }
}

void timer_install() {
    irq_install_handler(0, timer_handler);
}
