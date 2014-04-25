#ifndef PIT_H
#define PIT_H

#include "../isr/regs.h"

void timer_phase(int);
void timer_handler(regs*);
void timer_install();

#endif
